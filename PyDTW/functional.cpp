#include <ATen/ATen.h>
#include <ATen/NativeFunctions.h>
#include <ATen/native/cuda/DTW.cuh>
#include <torch/library.h>

namespace at {
namespace native {

// Forward declaration of the CUDA functions
Tensor dtw_forward_cuda(const Tensor& D);
Tensor dtw_backward_cuda(const Tensor& D, const Tensor& R);

// Forward function for DTW
Tensor dtw_forward(const Tensor& D) {
    if (D.is_cuda()) {
        return dtw_forward_cuda(D);
    } else {
        AT_ERROR("Not implemented on the CPU");
    }
}

// Backward function for DTW
Tensor dtw_backward(const Tensor& D, const Tensor& R) {
    if (D.is_cuda()) {
        return dtw_backward_cuda(D, R);
    } else {
        AT_ERROR("Not implemented on the CPU");
    }
}

TORCH_LIBRARY_IMPL(aten, CUDA, m) {
    m.impl("dtw_forward", dtw_forward);
    m.impl("dtw_backward", dtw_backward);
}

} // namespace native
} // namespace at
