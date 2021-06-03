#ifndef NETGAME_H
#define NETGAME_H
#include<QTcpServer>
#include<QTcpSocket>
#include<QMouseEvent>
#include<QMainWindow>
#include"game.h"
class Netgame:public Game{
 public:
    Q_OBJECT
public:
    Netgame(bool server);//构建
    void mousePressEvent(QMouseEvent *event);//获取鼠标信息
    QTcpServer*__fuwu__;
    QTcpSocket*__jieshou__;
public slots:
    void slotNewConnection();//链接网络;上传数据
    void slotRecv();//接受数据
};
#endif // NETGAME_H
