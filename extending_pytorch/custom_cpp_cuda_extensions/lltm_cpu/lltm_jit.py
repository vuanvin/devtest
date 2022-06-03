from typing import Tuple
from torch.utils.cpp_extension import load

lltm_cpp = load(name="lltm_cpp", sources=["lltm.cpp"], verbose=True)

print(lltm_cpp.forward)