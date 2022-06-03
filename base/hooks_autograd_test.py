import torch
from torch import autograd
from torch._C import autocast_decrement_nesting

x = torch.tensor(10., requires_grad=True)
v = torch.sin(x) + 10
w = v ** 2
y = w / 3

print(x, v, w, y)

grad = torch.autograd.grad(w, [v], retain_graph=True)
print(grad)
print(w.grad)

# grad = torch.autograd.grad(y, [x])
# print(x.grad)

def print_y_hook(grad):
    print('y: ', grad)

def print_v_hook(grad):
    print('v: ', grad)

y.register_hook(hook=print_y_hook)
v.register_hook(hook=print_v_hook)

y.backward()
print(y)