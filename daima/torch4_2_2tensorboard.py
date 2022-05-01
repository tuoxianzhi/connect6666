import torch
import numpy as np
import torch.nn as nn
import torch.nn.functional as F
from PIL import Image
from torchvision import transforms
from torchvision import models,datasets
from torch.utils.tensorboard import SummaryWriter
import tensorflow as tf
import tensorboard as tb
tf.io.gfile = tb.compat.tensorflow_stub.io.gfile
cat_img = Image.open('./440px-Felis_silvestris_catus_lying_on_rice_straw.jpg')
transform_224 = transforms.Compose([
        transforms.Resize(224), # 这里要说明下 Scale 已经过期了，使用Resize
        transforms.CenterCrop(224),
        transforms.ToTensor(),
    ])
cat_img_224=transform_224(cat_img)
writer = SummaryWriter(log_dir='./logs', comment='cat image') # 这里的logs要与--logdir的参数一样
writer.add_image("cat",cat_img_224)
writer.close()# 执行close立即刷新，否则将每120秒自动刷新

x = torch.FloatTensor([100])
y = torch.FloatTensor([500])

for epoch in range(30):
    x = x * 1.2
    y = y / 1.1
    loss = np.random.random()
    with SummaryWriter(log_dir='./logs', comment='train') as writer: #可以直接使用python的with语法，自动调用close方法
        writer.add_histogram('his/x', x, epoch)
        writer.add_histogram('his/y', y, epoch)
        writer.add_scalar('data/x', x, epoch)
        writer.add_scalar('data/y', y, epoch)
        writer.add_scalar('data/loss', loss, epoch)
        writer.add_scalars('data/data_group', {'x': x,
                                                'y': y}, epoch)
                                
BATCH_SIZE=512 
EPOCHS=20 
train_loader = torch.utils.data.DataLoader(
        datasets.MNIST('data', train=True, download=True, 
                       transform=transforms.Compose([
                           transforms.ToTensor(),
                           transforms.Normalize((0.1307,), (0.3081,))
                       ])),
        batch_size=BATCH_SIZE, shuffle=True)

class ConvNet(nn.Module):
    def __init__(self):
        super().__init__()
        # 1,28x28
        self.conv1=nn.Conv2d(1,10,5) # 10, 24x24
        self.conv2=nn.Conv2d(10,20,3) # 128, 10x10
        self.fc1 = nn.Linear(20*10*10,500)
        self.fc2 = nn.Linear(500,10)
    def forward(self,x):
        in_size = x.size(0)
        out = self.conv1(x) #24
        out = F.relu(out)
        out = F.max_pool2d(out, 2, 2)  #12
        out = self.conv2(out) #10
        out = F.relu(out)
        out = out.view(in_size,-1)
        out = self.fc1(out)
        out = F.relu(out)
        out = self.fc2(out)
        out = F.log_softmax(out,dim=1)
        return out
model = ConvNet()
optimizer = torch.optim.Adam(model.parameters())

from tensorboard.compat import tensorflow_stub

def train(model, train_loader, optimizer, epoch):
    n_iter=0
    model.train()
    for batch_idx, (data, target) in enumerate(train_loader):
        optimizer.zero_grad()
        output = model(data)
        loss = F.nll_loss(output, target)
        loss.backward()
        optimizer.step()
        if(batch_idx+1)%30 == 0: 
            n_iter=n_iter+1
            print('Train Epoch: {} [{}/{} ({:.0f}%)]\tLoss: {:.6f}'.format(
                epoch, batch_idx * len(data), len(train_loader.dataset),
                100. * batch_idx / len(train_loader), loss.item()))
            #相对于以前的训练方法 主要增加了以下内容
            out = torch.cat((output.data, torch.ones(len(output), 1)), 1) # 因为是投影到3D的空间，所以我们只需要3个维度
            with SummaryWriter(log_dir='./logs', comment='mnist') as writer: 
                #使用add_embedding方法进行可视化展示
                writer.add_embedding(
                    out,
                    metadata=target.data,
                    label_img=data.data,
                    global_step=n_iter)

train(model, train_loader, optimizer, 0)

vgg16 = models.vgg16(pretrained=True) # 这里下载预训练好的模型
print(vgg16) # 打印一下这个模型

transform_2 = transforms.Compose([
    transforms.Resize(224), 
    transforms.CenterCrop((224,224)),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406],
                                std=[0.229, 0.224, 0.225])
])

vgg16_input=transform_2(cat_img)[np.newaxis]# 因为pytorch的是分批次进行的，所以我们这里建立一个批次为1的数据集
vgg16_input.shape

out = vgg16(vgg16_input)
_, preds = torch.max(out.data, 1)
label=preds.numpy()[0]
label

with SummaryWriter(log_dir='./logs', comment='vgg161') as writer:
    writer.add_graph(vgg16, vgg16_input)