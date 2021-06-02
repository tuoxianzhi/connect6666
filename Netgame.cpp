#include "Netgame.h"
#include<QTcpServer>
#include<QTcpSocket>
Netgame::Netgame(bool server){
    __fuwu__=NULL;
    __jieshou__=NULL;
    if(server){
        __fuwu__=new QTcpServer(this);
        __fuwu__->listen(QHostAddress::Any,817);
        connect(__fuwu__,SIGNAL(newConnection()),this,SLOT(xinlianjie()));
    }
    else{
        __jieshou__=new QTcpSocket(this);
        __jieshou__->connectToHost(QHostAddress("127.0.0.1"),817);
        connect(__jieshou__,SIGNAL(readyRead()),this,SLOT(huishou()));
    }
}
void Netgame::slotNewConnection(){
    if(__jieshou__)return;
    __jieshou__=__fuwu__->nextPendingConnection();
    connect(__jieshou__,SIGNAL(readyRead()),this,SLOT(huishou()));
}
void Netgame::mousePressEvent(QMouseEvent *event){
    Game::mousePressEvent(event);
    int Board[441];
    char Board1[441];
    for(int i=0;i<21;i++)
        for(int j=0;j<21;j++)Board[i*21+j]=board[i][j]+1;
    for(int i=0;i<441;i++)Board1[i]=(char)Board[i];
    update();
    __jieshou__->write(Board1,441);
}
void Netgame::slotRecv(){
    QByteArray Ba=__jieshou__->readAll();
    int ba[21][21]={{0}};
    for(int i=0;i<21;i++)
        for(int j=0;j<21;j++)ba[i][j]=(int)Ba[i*21+j];
    for(int i=0;i<21;i++)
        for(int j=0;j<21;j++)board[i][j]=ba[i][j]-1;
    update();
}
