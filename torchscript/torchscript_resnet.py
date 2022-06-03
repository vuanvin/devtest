import torch
import torchvision

model = torchvision.models.resnet18()

# print(model)


x = torch.randn(5, 3, 224, 224)
y = torch.randn(5, 1000)


traced_model = torch.jit.trace(model, x)

scripted_model = torch.jit.script(model)

print(scripted_model.graph)

print('\n- - - - - - - - - - - - - - - - - - - - -\n')

print(traced_model.graph)