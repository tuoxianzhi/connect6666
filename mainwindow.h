#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include<QWidget>
#include"Game.h"
#include<QMouseEvent>
#include<QEvent>
#include"zhuye.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);//构建主页
    ~MainWindow();
    void paintEvent(QPaintEvent *);//绘图
    void mouseReleaseEvent(QMouseEvent *event);//获取
    void mouseMoveEvent(QMouseEvent *event);//获取鼠标位置并计算格子
    void init__game();//加载游戏
    void init__(char type);//开始新游戏
    void start_EVE();//开始eve游戏
    void isEnd();//判断是否游戏结束
    Game *game;
    QTimer *time1;
    char game_style;
    int suozaiX, suozaiY;
    char typeofgame;
    bool jinshou;
    bool xianshou;
    QPushButton*pushButton;
    QPushButton*pushButton2;
    QPushButton*pushButton3;
private slots:
    void renleixiaqi();//从鼠标获取人类下棋操作
    void AIxiaqi();//模拟ai下棋
    void flag();//为eve下棋传递
    void on_pushButton_clicked();//进行人人下棋
    void on_pushButton_2_clicked();//进行人机下棋
    void on_pushButton_3_clicked();//进行机机下棋
    void Internet();//进行联网下棋
public slots:
private:
    Ui::MainWindow *ui;
    zhuye page;
    QPushButton  *switch__;
};
#endif // MAINWINDOW_H
