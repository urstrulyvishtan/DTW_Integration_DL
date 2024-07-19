#pragma once

#include <ATen/ATen.h>
#include <c10/util/ArrayRef.h>

// CUDA kernel declarations
namespace at {
namespace native {

// Forward declaration of CUDA kernel functions
__global__ void compute_dtw_forward_cuda_kernel(const float* D, float* R, int N, int M);
__global__ void compute_dtw_backward_cuda_kernel(const float* D, const float* R, float* E, int N, int M);

// Function to compute DTW forward pass
Tensor dtw_forward_cuda(const Tensor& D);

// Function to compute DTW backward pass
Tensor dtw_backward_cuda(const Tensor& D, const Tensor& R);

} // namespace native
} // namespace at
