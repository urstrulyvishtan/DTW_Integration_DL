import unittest
import torch
from torch.autograd import gradcheck
from torch.testing import assert_allclose

# Import DTW functions
from torch_dtw import dtw_forward, dtw_backward

class TestDTW(unittest.TestCase):
    def setUp(self):
        # Define a simple Euclidean distance function
        self.dist_func = lambda x, y: torch.cdist(x, y, p=2)
        self.dtw = lambda x, y: dtw_forward(self.dist_func(x, y))
    
    def test_dtw_forward_basic():
        x = torch.tensor([[[0.0], [1.0], [2.0]]], dtype=torch.float32)
        y = torch.tensor([[[0.0], [1.0], [2.0], [3.0]]], dtype=torch.float32)
        dtw_dist = dtw_forward(x, y)
        expected_dtw_dist = torch.tensor([1.0], dtype=torch.float32)
        assert_allclose(dtw_dist, expected_dtw_dist)


    def test_dtw_forward_cpu(self):
        x = torch.randn(2, 10, 3, dtype=torch.float32)
        y = torch.randn(2, 15, 3, dtype=torch.float32)
        dtw_dist = self.dtw(x, y)
        self.assertEqual(dtw_dist.shape, torch.Size([2]))
        self.assertTrue(torch.isfinite(dtw_dist).all())

    def test_dtw_forward_cuda(self):
        if torch.cuda.is_available():
            x = torch.randn(2, 10, 3, dtype=torch.float32, device='cuda')
            y = torch.randn(2, 15, 3, dtype=torch.float32, device='cuda')
            dtw_dist = self.dtw(x, y)
            self.assertEqual(dtw_dist.shape, torch.Size([2]))
            self.assertTrue(torch.isfinite(dtw_dist).all())

    def test_dtw_backward_cpu(self):
        x = torch.randn(2, 10, 3, dtype=torch.float32, requires_grad=True)
        y = torch.randn(2, 15, 3, dtype=torch.float32, requires_grad=True)
        def func(x, y):
            return self.dtw(x, y)
        self.assertTrue(gradcheck(func, (x, y)))

    def test_dtw_backward_cuda(self):
        if torch.cuda.is_available():
            x = torch.randn(2, 10, 3, dtype=torch.float32, device='cuda', requires_grad=True)
            y = torch.randn(2, 15, 3, dtype=torch.float32, device='cuda', requires_grad=True)
            def func(x, y):
                return self.dtw(x, y)
            self.assertTrue(gradcheck(func, (x, y)))

    def test_dtw_values(self):
        x = torch.tensor([[[0.0], [1.0], [2.0]]], dtype=torch.float32)
        y = torch.tensor([[[0.0], [1.0], [2.0], [3.0]]], dtype=torch.float32)
        dtw_dist = self.dtw(x, y)
        expected_dtw_dist = torch.tensor([1.0], dtype=torch.float32)
        assert_allclose(dtw_dist, expected_dtw_dist)

    def test_dtw_forward_different_lengths():
        x = torch.tensor([[[1.0], [2.0], [3.0]]], dtype=torch.float32)
        y = torch.tensor([[[1.0], [2.0], [3.0], [4.0], [5.0]]], dtype=torch.float32)
        dtw_dist = dtw_forward(x, y)
        assert dtw_dist.shape == torch.Size([1])
        assert torch.isfinite(dtw_dist).all()

    def test_dtw_forward_empty():
        x = torch.tensor([[[0.0]]], dtype=torch.float32)
        y = torch.tensor([[[0.0]]], dtype=torch.float32)
        dtw_dist = dtw_forward(x, y)
        expected_dtw_dist = torch.tensor([0.0], dtype=torch.float32)
        assert_allclose(dtw_dist, expected_dtw_dist)

    def test_dtw_forward_batch():
        x = torch.tensor([[[0.0], [1.0], [2.0]], [[1.0], [2.0], [3.0]]], dtype=torch.float32)
        y = torch.tensor([[[0.0], [1.0], [2.0], [3.0]], [[2.0], [3.0], [4.0], [5.0]]], dtype=torch.float32)
        dtw_dist = dtw_forward(x, y)
        assert dtw_dist.shape == torch.Size([2])
        assert torch.isfinite(dtw_dist).all()
    
    def test_dtw_forward_cuda():
        if torch.cuda.is_available():
            x = torch.tensor([[[0.0], [1.0], [2.0]]], dtype=torch.float32, device='cuda')
            y = torch.tensor([[[0.0], [1.0], [2.0], [3.0]]], dtype=torch.float32, device='cuda')
            dtw_dist = dtw_forward(x, y)
            assert dtw_dist.shape == torch.Size([1])
            assert torch.isfinite(dtw_dist).all()
        
    def test_dtw_forward_gradcheck():
        x = torch.randn(2, 10, 3, dtype=torch.float32, requires_grad=True)
        y = torch.randn(2, 15, 3, dtype=torch.float32, requires_grad=True)
        def func(x, y):
            return dtw_forward(x, y)
        assert gradcheck(func, (x, y), eps=1e-6, atol=1e-4)

    def test_dtw_backward_basic():
        x = torch.tensor([[[0.0], [1.0], [2.0]]], dtype=torch.float32, requires_grad=True)
        y = torch.tensor([[[0.0], [1.0], [2.0], [3.0]]], dtype=torch.float32, requires_grad=True)
        D = dtw_forward(x, y)
        D.backward(torch.ones_like(D))
        assert x.grad is not None
        assert y.grad is not None

    def test_dtw_backward_gradcheck():
        x = torch.randn(2, 10, 3, dtype=torch.float32, device='cuda', requires_grad=True)
        y = torch.randn(2, 15, 3, dtype=torch.float32, device='cuda', requires_grad=True)
        def func(x, y):
            return dtw_forward(x, y)
        gradcheck(func, (x, y), eps=1e-6, atol=1e-4, device='cuda')

    def test_dtw_forward_non_finite():
        x = torch.tensor([[[float('inf')], [float('nan')], [2.0]]], dtype=torch.float32)
        y = torch.tensor([[[0.0], [1.0], [2.0], [3.0]]], dtype=torch.float32)
        dtw_dist = dtw_forward(x, y)
        assert not torch.isfinite(dtw_dist).all()

    def test_dtw_forward_large_sequences():
        x = torch.randn(2, 100, 3, dtype=torch.float32)
        y = torch.randn(2, 150, 3, dtype=torch.float32)
        dtw_dist = dtw_forward(x, y)
        assert dtw_dist.shape == torch.Size([2])
        assert torch.isfinite(dtw_dist).all()

if __name__ == '__main__':
    unittest.main()
