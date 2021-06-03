#include"mainwindow.h"
#include"zhuye.h"
#include"ui_mainwindow.h"
#include"Netgame.h"
#include<QMediaPlayer>
#include<QPaintEvent>
#include<QPushButton>
#include<QMouseEvent>
#include<QMessageBox>
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
#define CHESSONE  ":/new/prefix1/sound/chessone.wav"
#define BUTTON_CLICKED ":/new/prefix1/sound/button_clicked.wav"
#define BACK_SOUND  ":/new/prefix1/sound/kawaii.wav"
#define BACK_PIC    ":/new/prefix1/Image/fengdi.png"
#define LOGO        ":/new/prefix1/Image/star6.jpg"
const int qipan_size=20;
const int qidiansuozai=80;
const int gezichangdu=80;
const int mouseison=60;
const int flag_length=22;
const int r=35;
const int aithinktime=700;
void MainWindow::on_pushButton_clicked(){
    QSound::play(BUTTON_CLICKED);
    if(time1){
        time1->stop();
        delete time1;
        time1=nullptr;
    }
     ui->centralWidget->setMouseTracking(true);
     setMouseTracking(true);
     ui->pushButton->setMouseTracking(true);
     typeofgame=1;
     init__(typeofgame);
     ui->pushButton->setText("再来一局");
     ui->pushButton_2->setText("人机对决");
     ui->pushButton_3->setText("智能对决");
     update();
}
void MainWindow::on_pushButton_2_clicked(){
    QSound::play(BUTTON_CLICKED);
    if(time1){
        time1->stop();
        delete time1;
        time1=nullptr;
    }
    ui->centralWidget->setMouseTracking(true);
    this->setMouseTracking(true);
    ui->pushButton_2->setMouseTracking(true);
    typeofgame=2;
    init__(typeofgame);
    ui->pushButton->setText("人人对决");
    ui->pushButton_2->setText("再来一局");
    ui->pushButton_3->setText("智能对决");
    update();
}
void MainWindow::on_pushButton_3_clicked(){
    QSound::play(BUTTON_CLICKED);
    this->setMouseTracking(false);
    ui->pushButton->setText("人人对决");
    ui->pushButton_2->setText("人机对决");
    ui->pushButton_3->setText("再来一局");
    typeofgame=3;
    init__(typeofgame);
    srand((unsigned)time(nullptr));
    suozaiY=qipan_size/2;
    suozaiX=qipan_size/2;
    game->board[suozaiX][suozaiY]=1;
    QSound::play(CHESSONE);
    game->player=!game->player;
    start_EVE();
    update();
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setFixedSize(2*qidiansuozai+(qipan_size-1)*gezichangdu+800,2*qidiansuozai+(qipan_size-1)*gezichangdu);
    this->setWindowIcon(QPixmap(LOGO));
    /*ui->pushButton_2->setText("人机对决");
    ui->pushButton_3->setText("机机对决");
    ui->pushButton->setText("人人对决");
    ui->pushButton->setGeometry(2000,500,400,120);
    ui->pushButton_2->setGeometry(2000,900,400,120);
    ui->pushButton_3->setGeometry(2000,1300,400,120);
    ui->pushButton->setFont(QFont("华文彩云",20,1400));
    ui->pushButton_2->setFont(QFont("华文彩云",20,1400));
    ui->pushButton_3->setFont(QFont("华文彩云",20,1400));*/
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    pushButton=new QPushButton(this);
    pushButton->setText("AI帮你下！");
    pushButton->setGeometry(2000,900,400,120);
    pushButton->setFont(QFont("华文彩云",20,1400));
    if(typeofgame!=3)pushButton->show();
    connect(pushButton,&QPushButton::clicked,[=](){AIxiaqi();});
    pushButton2=new QPushButton(this);
    pushButton2->setText("返回主页面");
    pushButton2->setGeometry(2000,1300,400,120);
    pushButton2->setFont(QFont("华文彩云",20,1400));
    if(typeofgame!=3)pushButton2->show();
    connect(pushButton2,&QPushButton::clicked,[=](){page.show();this->close();});
    jinshou=true;
    xianshou=true;
    QMenuBar *menubar=menuBar();
    QMenu *menu_1=menubar->addMenu("规则介绍");
    QAction *action_1=menu_1->addAction("普通规则");
    QAction *guanyu=menu_1->addAction("关于禁手");
    QString str="规则:\n"
           "1.对峙双方谁的六个棋子先连在一条线即为胜者。\n"
           "2.当有四个子连成一条直线时，就应采取防守，堵住四子的一端，否则就会输掉比赛。\n"
           "3.应当避免在比赛内出现四四禁手、五五禁手等情况，否则就会不小心输掉比赛。\n";
    connect(action_1,&QAction::triggered,[=](){QMessageBox::about(this,"普通规则",str);});
    QMenu *xuanxiang=menubar->addMenu("选项");
    QAction *onoff=xuanxiang->addAction("关闭禁手");
    QAction *onoff1=xuanxiang->addAction("白方人机");
    connect(onoff,&QAction::triggered,[=](){jinshou=!jinshou;onoff->setText(jinshou?"关闭禁手":"开启禁手");});
    connect(onoff1,&QAction::triggered,[=](){xianshou=!xianshou;onoff1->setText(xianshou?"黑方人机":"白方人机");if(typeofgame==2)on_pushButton_2_clicked();});
    QAction *action_2=xuanxiang->addAction("爬");
    connect(action_2,&QAction::triggered,this,&QMainWindow::close);
    QString str_1="对局中禁止黑方使用的战术，即黑方一子落下时同时形成双四、双五或长连等三种棋形。黑方禁手的位置称为禁手点。\n";
    connect(guanyu,&QAction::triggered,[=](){QMessageBox::about(this,"禁手规则",str_1);});
    menu_1->addSeparator();
    QSound *backstartsound=new QSound(BACK_SOUND,this);
    backstartsound->play();
    backstartsound->setLoops(-1);
    init__game();
    this->close();
    page.show();
    void (zhuye::*mygame)()=&zhuye::signal1;
    void (zhuye::*mygame_2)()=&zhuye::signal2;
    void (zhuye::*mygame_3)()=&zhuye::signal3;
    void (zhuye::*mygame_4)()=&zhuye::signal4;
    connect(&page,mygame,this,[=](){this->show();page.hide();on_pushButton_clicked();});
    connect(&page,mygame_2,this,[=](){this->show();page.hide();on_pushButton_2_clicked();});
    connect(&page,mygame_3,this,[=](){this->show();page.hide();on_pushButton_3_clicked();});
    connect(&page,mygame_4,this,[=](){this->show();page.hide();Internet();});
}
void MainWindow::Internet(){
    QMessageBox::StandardButton ret;
    ret= QMessageBox::question(NULL,"server or client","是否作为服务器启动");
    if(ret==QMessageBox::Yes){
        Netgame*board=new Netgame(true);
        board->show();
    }
    else{
        Netgame*board=new Netgame(false);
        board->show();
    }
}
MainWindow::~MainWindow(){
    delete ui;
    if(game){
        delete game;
        game=nullptr;
    }
    if(time1){
        delete time1;
        time1=nullptr;
    }
}
void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(BACK_PIC));
    if((pushButton->underMouse())){
        painter.drawPixmap(1880,900,120,120,QPixmap(LOGO));
        painter.setRenderHint(QPainter::Antialiasing, true);
    }
    if((pushButton2->underMouse())){
        painter.drawPixmap(1880,1300,120,120,QPixmap(LOGO));
        painter.setRenderHint(QPainter::Antialiasing, true);
    }
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    for(int i=0;i<qipan_size;i++){
        painter.drawLine(qidiansuozai,qidiansuozai+i*gezichangdu,qidiansuozai+(qipan_size-1)*gezichangdu,qidiansuozai+i*gezichangdu);
        painter.drawLine(qidiansuozai+i*gezichangdu,qidiansuozai,qidiansuozai+i*gezichangdu,qidiansuozai+(qipan_size-1)*gezichangdu);
    }
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if(suozaiX>=0&&suozaiX<qipan_size&&suozaiY>=0&&suozaiY<qipan_size&&game->state==1&&game->board[suozaiX][suozaiY]==0){
        if(game->player){
            brush.setColor(Qt::black);
            painter.setBrush(brush);
            painter.drawRect(qidiansuozai+gezichangdu*suozaiX-flag_length/2,qidiansuozai+gezichangdu*suozaiY-flag_length/2,flag_length,flag_length);
        }
        else{
            brush.setColor(Qt::white);
            painter.setBrush(brush);
            painter.drawRect(qidiansuozai+gezichangdu*suozaiX-flag_length/2,qidiansuozai+gezichangdu*suozaiY-flag_length/2,flag_length,flag_length);
        }
    }
    for(int i=0;i<qipan_size;i++){
        for(int j=0;j<qipan_size;j++){
            if(game->board[i][j]==1&&game->state==1){
              brush.setColor(Qt::black);
              painter.setBrush(brush);
              painter.drawEllipse(QPoint(qidiansuozai+gezichangdu*i,qidiansuozai+gezichangdu*j),r,r);
           }
            else if(game->board[i][j]==-1&&game->state==1){
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint(qidiansuozai+gezichangdu*i,qidiansuozai+gezichangdu*j),r,r);
            }
        }
    }
    update();
}
void MainWindow::mouseMoveEvent(QMouseEvent *event){
    int x=event->x();
    int y=event->y();
    if (x>=qidiansuozai-mouseison&&x<=qidiansuozai+(qipan_size-1)*gezichangdu+mouseison&&
        y>=qidiansuozai-mouseison&&y<=qidiansuozai+(qipan_size-1)*gezichangdu+mouseison&&game->state==1){
        int hang=(x-qidiansuozai)/gezichangdu;
        int lie=(y-qidiansuozai)/gezichangdu;
        int zuoshangX=qidiansuozai+gezichangdu*hang;
        int zuoshangY=qidiansuozai+gezichangdu*lie;
        suozaiX=-1;
        suozaiY=-1;
        int len = 0;
        len=sqrt((x-zuoshangX)*(x-zuoshangX)+(y-zuoshangY)*(y-zuoshangY));
        if(x-zuoshangX<gezichangdu/2)suozaiX=hang;
        else suozaiX=hang+1;
        if(y-zuoshangY<gezichangdu/2)suozaiY=lie;
        else suozaiY=lie+1;
    }
    update();
}
void MainWindow::init__game(){
        game=new Game;
        time1=nullptr;
}

void MainWindow::init__(char type){
    if(game)delete game;
    game=new Game;
    game->typeofgame=type;
    game->state=1;
    if(time1){
        delete time1;
        time1=nullptr;
    }
    suozaiX=-1;
    suozaiY=-1;
    if(typeofgame==2&&!xianshou){
        srand((unsigned)time(nullptr));
        suozaiY=qipan_size/2;
        suozaiX=qipan_size/2;
        game->clear();
        game->board[suozaiX][suozaiY]=1;
        game->startgame1();
    }
    else game->startgame(type);
    update();
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event){
      if (suozaiX != -1 && suozaiY != -1&&game->state==1){
          if(typeofgame==1||game->player==xianshou) renleixiaqi();
          if(typeofgame==2&&game->player!=xianshou)QTimer::singleShot(aithinktime, this, SLOT(AIxiaqi()));
      }
      update();
}
void MainWindow::AIxiaqi(){
    game->AIcaozuo(suozaiX,suozaiY);
    QSound::play(CHESSONE);
    isEnd();
    update();
}
void MainWindow::renleixiaqi(){
    if (suozaiX!=-1&&suozaiY!=-1&&game->board[suozaiX][suozaiY]==0){
        game->updateqipan(suozaiX,suozaiY);
        QSound::play(CHESSONE);
        isEnd();
        update();
    }
}
void MainWindow::start_EVE(){
    time1=new QTimer(this);
    connect(time1,SIGNAL(timeout()),this,SLOT(flag()));
    time1->start(aithinktime);
}
void MainWindow::isEnd(){
    if(suozaiX>=0&&suozaiX<qipan_size&&suozaiY>=0&&suozaiY<qipan_size&&game->board[suozaiX][suozaiY]!=0){
        if(game->board[suozaiX][suozaiY]==1&&jinshou&&game->isjinshou(suozaiX,suozaiY)&&game->state==1){
            if(time1){
                time1->stop();
                time1=nullptr;
                page.show();
                this->close();
            }
            QMessageBox::StandardButton standar=QMessageBox::information(this,"游戏结束！","禁手！ White-player win！\n 点击Ok返回主界面！",QMessageBox::Ok);
            if(standar==QMessageBox::Ok){
                game->state=0;
                game->clear();
                page.show();
                this->close();
            }
        }
        else if(game->isWin(suozaiX,suozaiY)==true&&game->state==1){
            if(time1){
                time1->stop();
                time1=nullptr;
            }
            QString string;
            if(game->board[suozaiX][suozaiY]==1)string="Black-player win!";
            else string="White-player win!";
            QMessageBox::StandardButton standarbutton=QMessageBox::information(this," 游戏结束！",string+"\n"+" 点击Ok返回主界面!",QMessageBox::Ok);
            if(standarbutton==QMessageBox::Ok){
                game->state=0;
                game->clear();
            }
        }
        else if(game->isHeQi()&&game->state==1){
            if(time1){
                time1->stop();
                time1=nullptr;
            }
            game->state=0;
            QMessageBox::StandardButton standarbutton=QMessageBox::information(this,"游戏结束！","该局和棋啦！\n 点击Ok返回主界面",QMessageBox::Ok);
            if(standarbutton==QMessageBox::Ok){
                game->state=0;
                game->clear();
            }
        }
    }
}
void MainWindow::flag(){
    game->AIcaozuo(suozaiX,suozaiY);
    QSound::play(CHESSONE);
    isEnd();
}
