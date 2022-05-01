import torch
import numpy as np
import torch.nn as nn
import torch.nn.functional as F
from PIL import Image
from torchvision import transforms
from torchvision import models,datasets
import matplotlib.pyplot as plt
torch.__version__
cat_img=Image.open('./1280px-Felis_silvestris_catus_lying_on_rice_straw.jpg')
transform_224= transforms.Compose([
    transforms.Resize(224), 
    transforms.CenterCrop((224,224)),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406],
                                std=[0.229, 0.224, 0.225])
])


cat_img_224=transform_224(cat_img)
out = net(inputs)
_, preds = torch.max(out.data, 1)
preds
label=preds.numpy()[0]
label
import sys
sys.path.insert(0, './src/')
def rgb2gray(rgb):
    return np.dot(rgb[...,:3], [0.299, 0.587, 0.114])
def rescale_grads(map,gradtype="all"):
    if(gradtype=="pos"):    
        map = (np.maximum(0, map) / map.max())
    elif gradtype=="neg":
        map = (np.maximum(0, -map) / -map.min())
    else:
        map = map - map.min()
        map /= map.max()
    return map
    
inputs.requires_grad=True # 这句话必须要有，否则会报错
from guided_backprop import GuidedBackprop #这里直接引用写好的方法，在src，目录找想对应的文件
GB=GuidedBackprop(net)
gp_grads=GB.generate_gradients(inputs, label)
gp_grads=np.moveaxis(gp_grads,0,-1)
#我们分别计算三类的gp
ag=rescale_grads(gp_grads,gradtype="all")
pg=rescale_grads(gp_grads,gradtype="pos")
ng=rescale_grads(gp_grads,gradtype="neg")