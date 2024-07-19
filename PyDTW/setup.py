from setuptools import setup, Extension
from torch.utils.cpp_extension import CppExtension, CUDAExtension, BuildExtension

setup(
    name='torch_dtw',
    ext_modules=[
        CppExtension('torch_dtw_cpu', ['aten/src/ATen/native/cpu/DTW.cpp']),
        CUDAExtension('torch_dtw_cuda', [
            'aten/src/ATen/native/cuda/DTW.cu',
            'aten/src/ATen/native/functional.cpp'
        ])
    ],
    cmdclass={
        'build_ext': BuildExtension
    }
)
