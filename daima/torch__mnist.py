import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torchvision import datasets, transforms
import matplotlib.pyplot as plt
BATCH_SIZE=512
EPOCHS=20 
LR=0.005
DEVICE = torch.device("cuda" if torch.cuda.is_available() else "cpu") #判断是否使用GPU
def LOADER():
    '''data_loader=datasets.MNIST('data', train=True, download=True, 
                        transform=transforms.Compose([
                            transforms.ToTensor(),
                            transforms.Normalize((0.1307,), (0.3081,))
                        ]))
    train_size = int(0.8 * len(data_loader))
    test_size = len(data_loader) - train_size
    train_loader, test_loader = torch.utils.data.random_split(data_loader, [train_size, test_size])'''
    train_loader=datasets.MNIST('data', train=True, download=True, 
                        transform=transforms.Compose([
                            transforms.ToTensor(),
                            transforms.Normalize((0.1307,), (0.3081,))#minst的标准正态分布与期望
                        ]))
    test_loader=datasets.MNIST('data', train=False, download=True, 
                        transform=transforms.Compose([
                        transforms.ToTensor(),
                        transforms.Normalize((0.1307,), (0.3081,))
    ]))
    train_loader = torch.utils.data.DataLoader(
            train_loader,
            batch_size=BATCH_SIZE, shuffle=True,num_workers=0)
    
    test_loader = torch.utils.data.DataLoader(
            test_loader,
            batch_size=BATCH_SIZE, shuffle=True,num_workers=0)
    return test_loader,train_loader


class ConvNet(nn.Module):
    def __init__(self):
        super().__init__()# len=batch*1*28*28
        self.conv1 = nn.Conv2d(1, 10, 5) # 一层网络
        self.conv2 = nn.Conv2d(10, 20, 3) # 二层网络
        self.fc1 = nn.Linear(20*10*10, 500) # 二次导出
        self.fc2 = nn.Linear(500, 10) # 0-9十个分类
    def forward(self,x):
        in_size = x.size(0)#in_size=batch=512，x可以看成是512*1*28*28的张量。
        out = self.conv1(x)#batch*1*28*28 -> batch*10*24*24（28x28的图像经过一次核为5x5的卷积，输出变为24x24）
        out = F.relu(out)#batch*10*24*24relu函数激活）
        out = F.max_pool2d(out, 2, 2) # batch*10*24*24 -> batch*10*12*12重新池化
        out = self.conv2(out)#batch*10*12*12 -> batch*20*10*10
        out = F.relu(out)#batch*20*10*10
        out = out.view(in_size, -1)#batch*20*10*10 -> batch*2000
        out = self.fc1(out) # batch*2000 -> batch*500
        out = F.relu(out) # batch*500
        out = self.fc2(out) # batch*500 -> batch*10
        out = F.log_softmax(out, dim=1) # 计算log(softmax(x))的均值，二次激活
        return out

model = ConvNet().to(DEVICE)
optimizer = optim.Adam(model.parameters(),lr=LR)
#最优化步骤
data_los=[]
def train(model, device, train_loader, optimizer, epoch):
    #对model神经网络以train_loade为数据集，optimizer为优化方式，epoch为批次训练
    model.train()
    summ=0.
    for batch_idx, (data, target) in enumerate(train_loader):
        data, target = data.to(device), target.to(device)
        optimizer.zero_grad()
        #梯度置0
        output = model(data)
        #网络输入
        loss = F.nll_loss(output, target)
        #计算损失函数
        loss.backward()
        #反向求导
        optimizer.step()
        summ+=loss.item()
        if(batch_idx+1)%30 == 0: 
            print('Train Epoch: {} [{}/{} ({:.0f}%)]\tLoss: {:.6f}'.format(
                epoch, batch_idx * len(data), len(train_loader.dataset),
                100. * batch_idx / len(train_loader), loss.item()))
                #分批检验
        #print(sum)
    summ=summ/len(train_loader)
    data_los.append(summ)

datalos1=[]
def test(model, device, test_loader):
    #测试神经网络
    model.eval()#预处理模组
    test_loss = 0
    correct = 0
    sum=0.
    with torch.no_grad():
        #不求梯度检验
        for data, target in test_loader:
            
            data, target = data.to(device), target.to(device)
            output = model(data)
            test_loss += F.nll_loss(output, target, reduction='sum').item() 
            #损失累计
            pred = output.max(1, keepdim=True)[1] 
            # 找到解
            correct += pred.eq(target.view_as(pred)).sum().item()

    #test_loss /= len(test_loader.dataset)
    print('\nTest set: Average loss: {:.4f}, Accuracy: {}/{} ({:.2f}%)\n'.format(
        test_loss, correct, len(test_loader.dataset),
        100. * correct / len(test_loader.dataset)))
    datalos1.append(test_loss/len(test_loader.dataset))
        
if __name__== '__main__':
    test_loader,train_loader=LOADER()
    for epoch in range(1, EPOCHS + 1):
        train(model, DEVICE, train_loader, optimizer, epoch)
    test(model, DEVICE, test_loader)   
    '''ln1=plt.plot([i for i in range(1,EPOCHS+1)],data_los,color='red',linewidth=2.0,linestyle='--')
    ln2=plt.plot([i for i in range(1,EPOCHS+1)],datalos1,color='blue',linewidth=3.0,linestyle='-.')
    plt.title("lr=%f时训练集与测试集的损失"%LR)
    plt.legend(handles=[ln1,ln2],labels=['训练集损失','测试集损失'])
    plt.show()'''
    
    torch.save(model, '\model_minst.pkl')
    #保存神经网络