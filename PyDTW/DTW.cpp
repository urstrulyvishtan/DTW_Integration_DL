#include<ATen/ATen.h>
#include <ATen/cuda/CUDAContext.h>
#include <ATen/native/DTW.h>

namespace at{
    namespace native{
        Tensor dtw_forward_cuda(const Tensor& D){

        }

        Tensor dtw_backward_cuda(const Tensor& grad_output, const Tensor& D, const Tensor& R){
            
        }
    }
}