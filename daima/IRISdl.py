import torch
import torch.nn.functional as F
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from torch.autograd import Variable
import torch.nn as nn
from sklearn.datasets import load_iris
import pandas as pd
import numpy as np
from torch.utils import data
import time
iris = load_iris()

train_size = int(0.8 * len(iris))
test_size = len(iris) - train_size
train_loader, test_loader = torch.utils.data.random_split(iris, [train_size, test_size])
transfer_1 = PCA(n_components=2)
iris_data = pd.DataFrame(iris['data'])
iris_data[4] = iris['target']
iris_data = transfer_1.fit_transform(iris_data)
data_x = torch.from_numpy(iris_data)
data_y =torch.from_numpy(iris['target'])
data_x, data_y = Variable(data_x), Variable(data_y)
class LeNet(nn.Module):

    def __init__(self):
        super(LeNet, self).__init__()
        self.hid1 = nn.Linear(2, 10)
        self.hid2 = nn.Linear(10, 10)
        self.out = nn.Linear(10, 3)
    #隐藏层：2：10：10：3
    def forward(self, x):
        x = F.sigmoid(self.hid1(x))
        x = F.sigmoid(self.hid2(x))
        x = self.out(x)
        return x
        #采用sigmoid函数激活
# mehod 
'''torch.nn.Sequential(
    torch.nn.Linear(2, 10),
    torch.nn.Sigmoid(),
    torch.nn.Linear(10, 3),
    )
'''
def predict_it(x,y,my_net):
    predict = torch.max(my_net(x.float()), 1)[1]
    pred_y = predict.data.numpy()
    target_y = y.data.numpy()
    return float((pred_y == target_y).astype(int).sum()) / float(target_y.size)

#输出在神经网络net下，以（x，y）为样本的正确率

def machine_learn(x,y,learn_rate,loss_fun):
    
    begin=time.time()
    net=LeNet()
    optimizer = torch.optim.SGD(net.parameters(), lr=learn_rate)  #随机梯度下降
    loss_func = loss_fun
    for t in range(200):
        out = net(x.float())             
        loss = loss_func(out, y.long())  
        optimizer.zero_grad()  
        loss.backward()      
        optimizer.step()      
    '''
        if t % 10 == 0:
            # plot and show learning process
            predict = torch.max(net(x.float()), 1)[1]
            pred_y = predict.data.numpy()
            target_y = y.data.numpy()
            accuracy =predict_it(net)
            print( 'Progress to %d %%: Accuracy=%.2f' % (t/2,accuracy))'''
    #print('loss:',loss.item(),end=' ')
    
    end=time.time()
    print("time:",end-begin,end=' ')
    return net

#训练一个以（x，y）为样本，learndate为学习率，lossfun为损失函数的神经网络
if __name__=='__main__':
    #machine_learn()
    1==1
    net = LeNet()
    for i in range(1,10):
        learn_rate=float(i/10)
        net1=machine_learn(data_x[:134],data_y[:134],learn_rate,torch.nn.CrossEntropyLoss() )#采用交叉熵函数为损失
        accuracy=predict_it(data_x[135:],data_y[135:],net1)
        print('learnrate:',learn_rate)#输出成功率
    '''for t in range(200):
        
        out = net(x.float())                 # input x and predict based on x
        loss = loss_func(out, y.long())     # must be (1. nn output, 2. target), the target label is NOT one-hotted

        optimizer.zero_grad()   # clear gradients for next train
        loss.backward()         # backpropagation, compute gradients
        optimizer.step()        # apply gradients

        if t % 10 == 0:
            # plot and show learning process
            predict = torch.max(net(x.float()), 1)[1]
            pred_y = predict.data.numpy()
            target_y = y.data.numpy()
            accuracy =predict_it(net)
            print( 'Progress to %d %%: Accuracy=%.2f' % (t/2,accuracy))
            plt.pause(0.1)'''

