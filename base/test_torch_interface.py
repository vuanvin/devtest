import torch

import torch.autograd.function

print(torch._C._functions)
print(torch._C._functions.next_functions)