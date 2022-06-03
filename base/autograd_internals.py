import torch

x = torch.ones(2, 2, requires_grad=True)

print(x.grad_accumulator_)

y = x + 2
z = y * y * 3
out = z.mean()
z.backward()