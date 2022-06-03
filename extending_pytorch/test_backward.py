import torch
import torch.nn as nn

linear = nn.Linear(5, 5)

x = torch.randn(5, requires_grad=True)
t = torch.randn(5, requires_grad=True)

y: torch.Tensor = linear(x)
grad_x = torch.autograd.grad(y, x, t, retain_graph=True, create_graph=True)
print(grad_x)
print(x.grad)
