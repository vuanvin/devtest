import torch
from torch import cos, sin
from functools import reduce

pi = torch.pi
lm = torch.randn(1).item() # lambda

N = 10
n = torch.randn(N, dtype=torch.double)
k = torch.randn(N, dtype=torch.double)

h = torch.randn(N, dtype=torch.double, requires_grad=True)
print(h.clone().detach().numpy())
n_k = torch.complex(n, -k)

def forward(h: torch.Tensor):
    delta = ((2 * pi) / lm) * n_k * h

    img_i = torch.complex(torch.tensor(0.).double(), torch.tensor(1.).double()) # get complex symbol i

    Ms = [torch.stack([
            torch.stack([cos(delta[l]) , img_i * n_k[l] * sin(delta[l])]),
            torch.stack([img_i * sin(delta[l]) / n_k[l], cos(delta[l])]) 
          ]) for l in range(N)]

    M = reduce(torch.mm, Ms)
    t = 2 / M.sum()
    T = torch.norm(t)

    return T


optimizer = torch.optim.SGD([h], lr=0.05)

for epoch in range(10000):
    optimizer.zero_grad()
    T = -forward(h)
    T.backward()
    optimizer.step()

    if epoch % 1000 == 0:
        print(h.clone().detach().numpy())