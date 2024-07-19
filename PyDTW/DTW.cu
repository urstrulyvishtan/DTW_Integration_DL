#include <ATen/Aten.h>
#include <ATen/cuda/CUDAContext.h>
#include <THC/THCAtomics.cuh>
#include <ATen/native/cuda/DTW.cuh>
#include <cuda_runtime.h>

namespace at{
    namespace native{
        //cuda kernel to compute the forward DTW cost matrix
        template <typename scalar_t>
        __global__ void compute_dtw_cuda_kernel(
            const scalar_t* __restrict__ D, //Input distance matrix
            scalar_t* __restrict__ R, //cost matrix to br computed
            int64_t max_i, //Number of rows in the distance matrix
            int64_t max_j, //Number of columns in the distance matrix
            int64_t B
        ){
            int64_t b = blockIdx.x; //batch index
            int64_t tid = threadIdx.x; //thread index
            int64_t I = tid; //row index

            for(int64_t j = 1; j<=max_j; j++){
                for(int64_t i = 1; i<=max_i; i++){
                    if(I==i){
                        //retrieve values from the previous cells in the cost matrix
                        scalar_t r0 = R[b *(max_i + 1)*(max_j + 1)+(i - 1)*(max_j + 1)+(j -1)];
                        scalar_t r1 = R[b *(max_i + 1)*(max_j + 1)+(i - 1)*(max_j + 1)+j];
                        scalar_t r2 = R[b*(max_i + 1)*(max_j + 1)+i*(max_j + 1)+(j-1)];

                        //compute the cost for the current cell
                        R[b*(max_i + 1)*(max_j + 1)+i*(max_j + 1)+j] = D[b*max_i*max_j+(i-1)*max_j+(j-1)]+min(r0, min(r1, r2));
                    }
                }
                __syncthreads(); //synchronize threads within a block
            }
        }

        //cuda kernel to compute the backward DTW Gradients
        template <typename scalar_t>
        __global__ void compute_dtw_backwards_cuda_kernel(
            const scalar_t* __restrict__ D, // Input distance matrix
            const scalar_t* __restrict__ R, // forward cost matrix
            scalar_t* __restrict__ E, //gradient matrix to be computed
            int64_t max_i, //number of rows in the distance matrix
            int64_t max_j, //number of columns in the distance matrix
            int64_t B //batch size
        ){
            int64_t b = blockIdx.x; // batch index
            int64_t tid = threadIdx.x; //thread index
            int64_t I = tid; //row index

            for(int64_t j = max_j; j>0; j--){
                for(int64_t i = max_i; i>0; i--){
                    if(I==i){
                        //compute the gradients for the current cell
                        scalar_t a =(R[b * (max_i + 1)*(max_j + 1)+(i+1)*(max_j + 1)+j] - R[b * (max_i + 1)*(max_j + 1)+i*(max_j + 1) + j] - D[b * max_i * max_j + max_j * i + j]);
                        scalar_t b =(R[b * (max_i + 1)*(max_j + 1)+i*(max_j + 1)+(j + 1)] - R[b*(max_i + 1)*(max_j + 1)+i*(max_j + 1) + j] - D[b * max_i * max_j + i * max_j + (j+1)]);
                        scalar_t c =(R[b * (max_i + 1)*(max_j + 1)+(i+1)*(max_j + 1)+(j+1)] - R[b*(max_i + 1)*(max_j + 1)+i*(max_j + 1)+j] - D[b*max_i*max_j+(i+1)*max_j+(j+1)]);

                        //update the gradient matrix
                        E[b*(max_i + 1) * (max_j + 1) + i * (max_j + 1) + j] = E[b * (max_i + 1) + (i + 1) * (max_j + 1) + j] * a + E[b * (max_i + 1) * (max_j + 1) + i * (max_j + 1) + (j + 1)] * b + E[b * (max_i + 1) + (max_j + 1) * (i+1) * (max_j + 1) + (j + 1)] * c;
                    }
                }
                __syncthreads(); //Synchronize threads within a block
            }
        }
        //Function to launch the forward DTW CUDA kernel
        Tensor dtw_forward_cuda(const Tensor& D){
            auto D_ = D.continous(); //Ensure contiguous memory layout
            auto dev = D.device().index(); //get device index
            auto dtype = D.scalar_type(); //get data type

            int64_t B = D.size(0); //batch size
            int64_t N = D.size(1); //number of rows
            int64_t M = D.size(2); //number of columns
            int threads_per_block = max(N, M); //number of threads per block

            //initialize the cost matrix with infinity
            auto R = at::empty({B, N+1, M+1}, D.options().dtype(dtype).device(D.device()));
            R.fill_(std::numeric_limits<float>::infinity());
            R.select(1, 0).fill_(0); // set the first row to zero
            R.select(2, 0).fill_(0); // set the first column to zero

            // launch the CUDA kernel for forward DTW
            AT_DISPATCH_FLOATING_TYPES(D.scalar_type(), "dtw_forward_cuda", ([&] {
                compute_dtw_cuda_kernel<scalar_t><<<B, threads_per_block>>>(
                    D_.data_ptr<scalar_t>(),
                    R.data_ptr<scalar_t>(),
                    N,
                    M,
                    B
                );
            }));

            //return the last element of the cost matrix (DTW distance)
            return R.select(1, N).select(1, M);
        }
        // Function to launch the backward DTW CUDA kernel
        Tensor dtw_backward_cuda(const Tensor& grad_output, const Tensor& D, const Tensor& R){
            auto D_ = D.contiguous(); //Ensure contiguous memory layout
            auto R_ = R.contiguous(); //Ensure contiguous memory layout
            auto dev = D.device().index(); //get device index
            auto dtype = D.scalar_type(); //get data type

            int64_t B = D.size(0); //batch size
            int64_t N = D.size(1); //number of rows
            int64_t M = D.size(2); //number of columns
            int threads_per_block = max(N, M); //number of threads per block

            //initialize the gradient matrix with zeros
            auto E = at::zeros({b, N+1, M+1}, D.options().dtype(dtype).device(D.device()));
            E.select(1, N).select(1, M).fill_(1); //set the last element to one

            // launch the CUDA kernel for backward DTW
            AT_DISPATCH_FLOATING_TYPES(D.scalar_type(), "dtw_backward_cuda", ([&] {
                compute_dtw_backwards_cuda_kernel<scalar_t><<<B, threads_per_block>>>(
                    D_.data_ptr<scalar_t>(),
                    R_.data_ptr<scalar_t>(),
                    E.data_ptr<scalar_t>(),
                    N,
                    M,
                    B
                );
            }));

            //return the gradient matrix excluding the padding
            return E.select(1,1).select(1,1);
        }
    } //namespace native
}   //namespace at