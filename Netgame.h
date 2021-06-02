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
    Netgame(bool server);
    void mousePressEvent(QMouseEvent *event);
    QTcpServer*__fuwu__;
    QTcpSocket*__jieshou__;
public slots:
    void slotNewConnection();
    void slotRecv();
};

#endif // NETGAME_H
