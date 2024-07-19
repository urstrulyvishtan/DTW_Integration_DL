import torch
from torch.autograd import Function
from torch import nn
from . import _C

class DTWFunction(Function):
    @staticmethod
    def forward(ctx, D):
        #save the input tensor for the backward pass
        ctx.save_for_backward(D)

        #call the forward function based on the device of the input tensor
        if D.is_cuda:
            return _C.dtw_forward_cuda(D)
        else:
            return _C.dtw_forward(D)
        
    @staticmethod
    def backward(ctx, grad_output):
        #retrieve the saved input tensor
        D, = ctx.saved_tensors

        #call the backward function based on the device of the input tensor
        if D.is_cuda:
            return _C.dtw_backward_cuda(grad_output, D, ctx.saved_variables[1])
        else:
            return _C.dtw_backward(grad_output, D, ctx.saved_variables[1])
        
class DTW(nn.module):
    def __init__(slef, dist_func):
        super(DTW, self).__init__()
        self.dist_func = dist_func
    
    def forward(self, x, y):
        #compute the distance matrix using the provided distance funciton
        D = self.dist_func(x, y)

        #call the DTW function
        return DTWFunction.apply(D)
        