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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Game *game;
    QTimer *time1;
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    char game_style;
    int suozaiX, suozaiY;
    void init__game();
    char typeofgame;
    bool jinshou;
    bool xianshou;
    void init__(char type);
    void start_EVE();
    QPushButton*pushButton;
    QPushButton*pushButton2;
    QPushButton*pushButton3;
    void isEnd();
private slots:
    void renleixiaqi();
    void AIxiaqi();
    void flag();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void Internet();
public slots:
private:
    Ui::MainWindow *ui;
    zhuye page;
    QPushButton  *switch__;
};
#endif // MAINWINDOW_H
