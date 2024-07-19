#include<ATen/ATen.h>
#include <ATen/cuda/CUDAContext.h>
#include <ATen/NativeFunctions.h>
#include <ATen/native/TensorIterator.h>
#include <ATen/native/cuda/DTW.cuh>

namespace at{
    namespace native{
        // Function to compute DTW on the CPU
        Tensor dtw_forward(const Tensor& D){
            //check the input tensor properties
            TORCH_CHECK(D.dim() == 3, "Input distance matrix must be a 3D tensor");
            auto D_ = D.contiguous(); //Ensure Contiguous memory layout

            int64_t B = D.size(0); // Batch size
            int64_t N = D.size(1); // Number of rows
            int64_t M = D.size(2); // Number of columns

            // Initailize the cost matrix with infinity
            auto R = at::empty({B, N+1, M+1}, D.options());
            R.fill_(std::numeric_limits<float>::infinity());
            R.select(1, 0).fill_(0); //set the first row to zero
            R.select(2, 0).fill_(0); //set the first column to zero

            // compute the cost matrix on the CPU
            for(int64_t b = 0; b<B; ++b){
                for(int64_t j = 1; j<=M; ++j){
                    for(int64_t i = 1; i<=N; ++i){
                        float r0 = R[b][i-1][j-1].item<float>();
                        float r1 = R[b][i-1][j].item<float>();
                        float r2 = R[b][i][j-1].item<float>();
                        R[b][i][j] = D[b][i-1][j-1] + std::min({r0, r1, r2});
                    }
                }
            }
            // Return the last element of the cost matrix (DTW distance)
            return R.select(1, N).select(1, M);
        }

        // Function to compute DTW gradients on the CPU
        Tensor dtw_backward(const Tensor& grad_output, const Tensor& D, const Tensor& R){
            auto D_ = D.contiguous(); // Ensure contigous memory layout
            auto R_ = R.contiguous(); // Ensure contiguous memory layout

            int64_t B = D.size(0); // Batch size
            int64_t N = D.size(1); // Number of rows
            int64_t M = D.size(2); // Number of Columns

            // Initialize the gradient matrix with zeros
            auto E = at::zeros({B, N+1, M+1}, D.options());
            E.select(1, N).select(1, M).fill_(1); // set the last element to one

            // compute the gradient matrix on the CPU
            for(int64_t b = 0; b<B; ++b){
                for(int64_t j = M; j>0; --j){
                    for(int64_t i = N; i>0; --i){
                        float a = (R[b][i+1][j].item<float>() - R[b][i][j].item<float>() - D[b][i+1][j].item<float>());
                        float b = (R[b][i][j+1].item<float>() - R[b][i][j].item<float>() - D[b][i][j+1].item<float>());
                        float c = (R[b][i+1][j+1].item<float>() - R[b][i][j].item<float>() - D[b][i+1][j+1].item<float>());
                        E[b][i][j] = E[b][i+1][j] * a + E[b][i][j+1] * b + E[b][i+1][j+1] * c;
                    }
                }
            }
            // return the gradient matrix excluding the padding
            return E.select(1, 1).select(1, 1);
        }

        // Function to compute DTW on the CUDA GPU
        Tensor dtw_forward_cuda(const Tensor& D){
            // calling the CUDA funtion from the cu file
            return dtw_forward_cuda(D);
        }
        
        // Function to compute the DTW gradients on the CUDA GPU
        Tensor dtw_backward_cuda(const Tensor& grad_output, const Tensor& D, const Tensor& R){
            // call the CUDA function from the cu file
            return dtw_backward_cuda(grad_output, D, R);
        }

        // register the DTW forward and backward functions
        REGISTER_DISPATCH(dtw_forward_stub, &dtw_forward);
        REGISTER_DISPATCH(dtw_backward_stud, &dtw_backward);
    } // namespace native
}   // namespace at