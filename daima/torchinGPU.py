from numpy.core.fromnumeric import mean
from torch.autograd import Variable
import torch
import sympy as sp
import numpy as np
x = torch.tensor([1.,2.],requires_grad=True)
y=[x+2,x+3]
print(y)