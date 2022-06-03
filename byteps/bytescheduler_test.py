import torch
import torch.optim as optim
from torchvision import models
import horovod.torch as hvd

# Set up standard model.
model = getattr(models, "resnet50")()
optimizer = optim.SGD(model.parameters(), lr=0.01)

# bytescheduler wrapper
import bytescheduler.pytorch.horovod as bsc
bsc.init()

# Horovod: wrap optimizer with DistributedOptimizer.
optimizer = hvd.DistributedOptimizer(optimizer,
                                     named_parameters=model.named_parameters(),
                                     compression=hvd.Compression.none)
num_steps = 1000

# ByteScheduler, further wrap Horovod DistributedOptimizer
optimizer = bsc.ScheduledOptimizer(model, optimizer, num_steps)
