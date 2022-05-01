import torch
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torchvision import datasets, transforms
from torch__mnist import ConvNet
import cv2
import numpy as np
import torch
import glob
import cv2
import torch.nn.functional as F
from torch.autograd import Variable
from torchvision import datasets, transforms
import numpy as np
import torchvision
from skimage import io,transform
import time
BATCH_SIZE=512 #大概需要2G的显存
EPOCHS=20 # 总共训练批次
DEVICE = torch.device("cuda" if torch.cuda.is_available() else "cpu") 
data_set=datasets.MNIST('data', train=True, download=True, 
                       transform=transforms.Compose([
                           transforms.ToTensor(),
                           transforms.Normalize((0.1307,), (0.3081,))
                       ]))

test_loader = torch.utils.data.DataLoader(
        data_set,
        batch_size=BATCH_SIZE, shuffle=True,num_workers=0)

def test(model, device, test_loader):
    model.eval()
    test_loss = 0
    correct = 0
    with torch.no_grad():
        for data, target in test_loader:
            
            data, target = data.to(device), target.to(device)
            output = model(data)
            test_loss += F.nll_loss(output, target, reduction='sum').item() # 将一批的损失相加
            pred = output.max(1, keepdim=True)[1] # 找到概率最大的下标
            correct += pred.eq(target.view_as(pred)).sum().item()

    test_loss /= len(test_loader.dataset)
    print('\nTest set: Average loss: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(
        test_loss, correct, len(test_loader.dataset),
        100. * correct / len(test_loader.dataset)))
def conversion(path,size):
    img=cv2.imread(path,0)
    img=cv2.resize(img,size)
    high,width=img.shape
    dst=np.zeros((high,width),np.uint8)
    for i in range(high):
        for j in range(width):
            dst[i,j]=255-img[i,j]
            if dst[i,j]>0: dst[i,j]=255    
    img=dst
#    time.sleep()
    img=np.array(img).astype(np.float32)
    img=np.expand_dims(img,0)
    img=np.expand_dims(img,0)#扩展后，为[1，1，28，28]
    img=torch.from_numpy(img)
    img = img.to(DEVICE)
    img=Variable(img)
    return img 

if __name__== '__main__':
    model1 = torch.load('\model_minst.pkl')
    output=model1(conversion(r"D:\TOM\write\pypypy\torch\mydata\three.jpg",(28,28)))
    prob = F.softmax(output, dim=1)
    prob = Variable(prob)
    prob = prob.cpu().numpy() 
    pred = np.argmax(prob) #选出概率最大的一个
    print(pred.item())