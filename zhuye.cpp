#include"zhuye.h"
#include<QMediaPlayer>
#include<QPaintEvent>
#include<QPushButton>
#include<QMouseEvent>
#include<QMessageBox>
#include<QMainWindow>
#include<qtimer.h>
#include<QMenuBar>
#include<QPainter>
#include<QBitmap>
#include<QPixmap>
#include<qmath.h>
#include<QBrush>
#include<QDebug>
#include<QSound>
#include<QLabel>
#include<QMenu>
#include<QIcon>
#include<QPen>
#define BACK ":/new/prefix1/Image/qihun1.jpg.png"
#define BUTTON_CLICKED ":/new/prefix1/sound/button_clicked.wav"
#define LOGO        ":/new/prefix1/Image/star6.jpg"
zhuye::zhuye(QWidget *parent) : QWidget(parent){
    this->setWindowIcon(QPixmap(LOGO));
    setWindowTitle("Connect6!!!");
    this->setFixedSize(2560,1760);
    pushbutton=new QPushButton(this);
    pushbutton->setFont(QFont("宋体",40,1200));
    pushbutton->move(QPoint(900,1200));
    pushbutton->setFixedSize(600,160);
    pushbutton->setText("人人游戏");
    pushbutton->setFlat(true);
    connect(pushbutton,&QPushButton::clicked,this,[=](){emit signal1();});
    connect(pushbutton,&QPushButton::clicked,this,[=](){emit QSound::play(BUTTON_CLICKED);});
    pushbutton_2=new QPushButton(this);
    pushbutton_2->setFont(QFont("宋体",40,1200));
    pushbutton_2->move(QPoint(1700,1200));
    pushbutton_2->setFixedSize(600,160);
    pushbutton_2->setText("人机游戏");
    pushbutton_2->setFlat(false);
    connect(pushbutton_2,&QPushButton::clicked,this,[=](){emit signal2();});
    connect(pushbutton_2,&QPushButton::clicked,this,[=](){emit QSound::play(BUTTON_CLICKED);});
    pushbutton_3=new QPushButton(this);
    pushbutton_3->setFont(QFont("宋体",40,1200));
    pushbutton_3->move(QPoint(100,1200));
    pushbutton_3->setFixedSize(600,160);
    pushbutton_3->setText("机机游戏");
    pushbutton_3->setFlat(false);
    connect(pushbutton_3,&QPushButton::clicked,this,[=](){emit signal3();});
    connect(pushbutton_3,&QPushButton::clicked,this,[=](){emit QSound::play(BUTTON_CLICKED);});
    pushbutton_1=new QPushButton(this);
    pushbutton_1->setFont(QFont("宋体",20,600));
    pushbutton_1->move(QPoint(450,1500));
    pushbutton_1->setFixedSize(300,80);
    pushbutton_1->setText("关于作者");
    pushbutton_1->setFlat(false);
    QString str="作者：南京理工大学\n920106970136王韬\n";
    connect(pushbutton_1,&QPushButton::clicked,[=](){QMessageBox::about(this,"关于作者",str);});
    connect(pushbutton_1,&QPushButton::clicked,this,[=](){emit QSound::play(BUTTON_CLICKED);});
    pushbutton_4=new QPushButton(this);
    pushbutton_4->setFont(QFont("宋体",20,600));
    pushbutton_4->move(QPoint(1600,1500));
    pushbutton_4->setFixedSize(300,80);
    pushbutton_4->setText("联网游戏");
    pushbutton_4->setFlat(false);
    connect(pushbutton_4,&QPushButton::clicked,this,[=](){emit signal4();});
    connect(pushbutton_4,&QPushButton::clicked,this,[=](){emit QSound::play(BUTTON_CLICKED);});
}
void zhuye::paintEvent(QPaintEvent *event){
    pushbutton->setFlat(pushbutton->underMouse());
    pushbutton_1->setFlat(pushbutton_1->underMouse());
    pushbutton_2->setFlat(pushbutton_2->underMouse());
    pushbutton_3->setFlat(pushbutton_3->underMouse());
    pushbutton_4->setFlat(pushbutton_4->underMouse());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(BACK));
}
