import torch

x = torch.tensor(1.1, requires_grad=True)
print(x._version)

v = x.tanh()

y = v * 2
print(y._version)

y = y.add_(3)
# y = y + 3

print(y._version)
y.backward()

print(y)