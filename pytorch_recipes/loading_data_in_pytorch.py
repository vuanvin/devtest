import torch
import torchaudio

root = '/tmp/yesno'

# torchaudio.datasets.YESNO(
#      root,
#      url='http://www.openslr.org/resources/1/waves_yesno.tar.gz',
#      folder_in_archive='waves_yesno',
#      download=False,
#      transform=None,
#      target_transform=None)

# * ``download``: If true, downloads the dataset from the internet and puts it in root directory. If dataset is already downloaded, it is not downloaded again.
# * ``transform``: Using transforms on your data allows you to take it from its source state and transform it into data that’s joined together, de-normalized, and ready for training. Each library in PyTorch supports a growing list of transformations.
# * ``target_transform``: A function/transform that takes in the target and transforms it.
#
# Let’s access our Yesno data:
#

# A data point in Yesno is a tuple (waveform, sample_rate, labels) where labels
# is a list of integers with 1 for yes and 0 for no.
yesno_data = torchaudio.datasets.YESNO('./', download=True)

# Pick data point number 3 to see an example of the the yesno_data:
n = 3
waveform, sample_rate, labels = yesno_data[n]
print("Waveform: {}\nSample rate: {}\nLabels: {}".format(waveform, sample_rate, labels))

data_loader = torch.utils.data.DataLoader(yesno_data,
                                          batch_size=1,
                                          shuffle=True)

for data in data_loader:
  print("Data: ", data)
  print("Waveform: {}\nSample rate: {}\nLabels: {}".format(data[0], data[1], data[2]))
  break

import matplotlib.pyplot as plt

print(data[0][0].numpy())

plt.figure()
plt.plot(waveform.t().numpy()) # t表示转置
