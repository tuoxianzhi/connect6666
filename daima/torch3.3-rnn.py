import torch
from torch import nn
import numpy as np
import matplotlib as mat
mat.use("TkAgg")
import matplotlib.pyplot as plt
import time
from torch.autograd import Variable
import cv2
torch.manual_seed(1)    # reproducible

LR = 0.02           # learning rate
class LSNN(nn.Module):
    def __init__(self):
        super(LSNN, self).__init__()
        self.lstm = nn.LSTM(
            input_size=2,
            hidden_size=32,     # rnn hidden unit
            num_layers=1, # 有几层 RNN layers
            batch_first=True,   # input & output 会是以 batch size 为第一维度的特征集 e.g. (batch, time_step, input_size)

        )
        self.hidden = (torch.autograd.Variable(torch.zeros(1, 1, 32)),torch.autograd.Variable(torch.zeros(1, 1, 32)))#1表示隐藏层数目，1表示批数目，32表示隐藏层size，lstm有两个状态矩阵
        self.out = nn.Linear(32, 1)

    def forward(self,x):
        # x (batch_size, time_step, input_size)(批量，[值1,值2]，输入层数目)
        # h_state (n_layers, batch_size, hidden_size)
        # r_out (batch, time_step, output_size)
        r_out,self.hidden= self.lstm(x,self.hidden)   # h_state 也要作为 RNN 的一个输入
        self.hidden=(Variable(self.hidden[0]),Variable(self.hidden[1]))#可以把这一步去掉，在loss.backward（）中加retain_graph=True，主要是Varible有记忆功能，而张量没有
       # outs = []    # 保存所有时间点的预测值
        print(r_out.size())
        results=self.out(r_out)
        print(results.size())
        return results.view(-1,50,1)
'''
        for time_step in range(r_out.size(1)):    # 对每一个时间点计算 output
            outs.append(self.out(r_out[:, time_step, :]))
        return torch.stack(outs, dim=1)


    def forward(self, x):
        r_out,self.hidden= self.rnn(x, h_state)
        r_out = r_out.view(-1, 32)
        outs = self.out(r_out)
        return outs.view(-1, 10, 1), h_state
'''


lstmNN = LSNN()
print(lstmNN)
optimizer = torch.optim.Adam(lstmNN.parameters(), lr=LR)  # optimize all rnn parameters
loss_func = nn.MSELoss()



  # 要使用初始 hidden state, 可以设成 None
for step in range(10000):
    start, end = 0,2*np.pi   # time steps
    # sin 预测 cos
    steps = np.linspace(start, end, 50, dtype=np.float32)
    x_np =np.hstack((steps.reshape((-1,1)),np.sin(steps).reshape(-1,1)))# float32 for converting torch FloatTensor
    y_np =np.array([np.cos(steps)])
    #print(x_np)

    x = Variable(torch.from_numpy(x_np[np.newaxis,:,np.newaxis])) # shape (batch, time_step, input_size)
    y = Variable(torch.from_numpy(y_np[np.newaxis,:,np.newaxis]))
    x=x.view(1,-1,2)#(-1,inputsize,inputsize),这一步很重要，输入有几个这样设置，会变成三个维度的张量，1表示只分一批训练，-1表示这一批默认的总数，2表示输入的size
    y=y.view(1,-1,1)#和主要要和prediction对应，1表示batch——first为一批，后一个表示输出的size
    print(x.size(),y.size())


    prediction = lstmNN(x)   # rnn 对于每个 step 的 prediction, 还有最后一个 step 的 h_state


    loss = loss_func(prediction, y)     # cross entropy loss
    optimizer.zero_grad()               # clear gradients for this training step
    loss.backward()                     # backpropagation, compute gradients
    optimizer.step()
    # apply gradients
    plt.ion()
    line_sin=plt.plot(steps, np.sin(steps), 'r-')
    line_cos=plt.plot(steps, prediction.data.numpy().flatten(), 'b-')
    plt.plot(steps,y.data.numpy().flatten(),"orange")
    plt.draw()
    plt.pause(0.05)
    #plt.ioff()
    plt.show()
    plt.setp(line_cos,visible=False)
plt.pause(100)
