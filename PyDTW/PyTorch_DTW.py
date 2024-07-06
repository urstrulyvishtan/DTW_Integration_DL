import numpy as np
import torch
import torch.cuda
from numba import jit, prange
from torch.autograd import Function
from numba import cuda
import math

@cuda.jit
def compute_dtw_cuda(D, max_i, max_j, R):
    """
    Compute the DTW distance between two sequences using CUDA. Cost Matrix.

    Parameters:
    - D: Input distance matrix
    - max
    """
    b = cuda.blockIdx.x
    tid = cuda.threadIdx.x 

    I= tid

    for j in range(1, max_j + 1):
        for i in range(1, max_i+1):
            if I == i:
                r0 = R[b, i-1, j-1]
                r1 = R[b, i-1, j]
                r2 = R[b, i, j-1]
                R[b, i, j ]=D[b, i-1, j-1] + min(r0, r1, r2)
        cuda.syncthreads()

    
@cuda.jit
def compute_dtw_backwards_cuda(D, R, max_i, max_j, E):

    b = cuda.blockIdx.x
    tid = cuda.threadIdx.x

    I = tid

    for j in range(max_j, 0, -1):
        for i in range(max_i, 0, -1):
            if I == i:
                a = (R[b, i+1, j] - R[b, i, j] - D[b, i+1, j])
                b = (R[b, i, j+1] - R[b, i, j] - D[b, i, j+1])
                c = (R[b, i+1, j+1] - R[b, i, j] - D[b, i+1, j+1])
                E[b, i, j] = E[b, i+1, j]* a + E[b, i, j+1] * b + E[b, i+1, j+1] * c
        cuda.syncthreads()


class _DTWCUDA(Function):
    @staticmethod
    def forward(ctx, D):
        dev = D.device
        dtype = D.dtype

        B = D.shape[0]
        N = D.shape[1]
        M = D.shape[2]
        threads_per_block = max(N, M)

        R = torch.ones((B, N+1, M+1), device = dev, dtype=dtype)*math.inf

        R[:, 0, 0] = 0

        compute_dtw_backwards_cuda[B, threads_per_block](cuda.as_cuda_array(D.detach()), N, M, cuda.as_cuda_array(R))
        ctx.save_for_backward(D, R.clone())
        return R[:, -1, -1]
    

    @staticmethod
    def backward(ctx, grad_output):
        dev = grad_output.device
        dtype = grad_output.dtype
        D, R = ctx.saved_tensors

        B = D.shape[0]
        N = D.shape[1]
        M = D.shape[2]
        threads_per_block = max(N,M)

        D_ = torch.zeros((B, N + 1, M + 1), dtype = dtype, device = dev)

        R[:, :, -1] = -math.inf
        R[:, -1, :] = -math.inf
        R[:, -1, -1] = R[:, -2, -2]

        E = torch.zeros((B, N+1, M+1), dtype = dtype, device = dev)
        E[:, -1, -1]= 1

        compute_dtw_backwards_cuda[B, threads_per_block](cuda.as_cuda_array(D_), cuda.as_cuda_array(R), N, M, cuda.as_cuda_array(E))
        E = E[:, 1:N+1, 1:M+1]

        return grad_output.view(-1, 1, 1).expand_as(E), None
    

@jit(nopython = True, parallel = True)
def compute_dtw(D):

    B = D.shape[0]
    N = D.shape[1]
    M = D.shape[2]
    R = np.ones((B, N+1, M+1)) * np.inf
    R[:, 0, 0] = 0
    for b in prange(B):
        for j in range(1, M+1):
            for i in range(1, N+1):
                r0 = R[b, i-1, j-1]
                r1 = R[b, i-1, j]
                r2 = R[b, i, j-1]
                R[b, i, j] = D[b, i-1, j-1] + min(r0+ r1+ r2)
    return R


@jit(nopython = True, parallel = True)
def compute_dtw_backward(D_, R):

    B = D_.shape[0]
    N = D_.shape[1]
    M = D_.shape[2]
    D = np.zeros((B, N+1, M+1))
    E = np.zeros((B, N+1, M+1))
    D[:,1:N+1, 1:M+1] = D_
    E[:, -1, -1] = 1
    R[:, :, -1] = -np.inf
    R[:, -1, :] = -np.inf
    R[:, -1, -1] = R[:, -2, -2]
    for k in prange(B):
        for j in range(M, 0, -1):
            for i in range(N, 0, -1):
                a = (R[k, i+1, j] - R[k, i, j] - D[k, i+1, j])
                b = (R[k, i, j+1] - R[k, i, j] - D[k, i, j+1])
                c = (R[k, i+1, j+1] - R[k, i, j] - D[k, i+1, j+1])
                E[k, i, j] = E[k, i+1, j] * a + E[k, i, j+1] * b + E[k, i+1, j+1] * c

    return E[:, 1:N+1, 1:M+1]

class _DTW(Function):
    @staticmethod
    def forward(ctx, D):
        dev = D.device
        dtype = D.dtype
        D_ = D.detach().cpu().numpy()
        R = torch.Tensor(compute_dtw(D_)).to(dev).type(dtype)
        ctx.save_for_backward(D, R)
        return R[:, -1, -1]
    
    @staticmethod
    def backward(ctx, grad_output):
        dev = grad_output.device
        dtype = grad_output.dtype
        D, R = ctx.saved_tensors
        D_ = D.detach().cpu().numpy()
        E = torch.Tensor(compute_dtw_backward(D_, R.detach().cpu().numpy())).to(dev).type(dtype)
        return grad_output.view(-1, 1, 1).expand_as(E) * E, None
    

class DTW(torch.nn.Module):
    def __init__(self, dist_func):
        super(DTW, self).__init__()
        self.dist_func = dist_func

    @staticmethod
    def _get_func_dtw(x, y):
        return _DTWCUDA.apply if x.is_cuda else _DTW.apply
    
    def forward(self, x, y):
        D = self.dist_func(x, y)
        func_dtw = self._get_func_dtw(x, y)
        return func_dtw(D)
