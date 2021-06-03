#ifndef ZHUYE_H
#define ZHUYE_H
#include<QWidget>
#include<QPushButton>
class zhuye : public QWidget{
    Q_OBJECT
public:
    explicit zhuye(QWidget *parent = nullptr);//构建主页
    void paintEvent(QPaintEvent *event);//绘图建立主页
    QPushButton *pushbutton;
    QPushButton *pushbutton_1;
    QPushButton *pushbutton_2;
    QPushButton *pushbutton_3;
    QPushButton *pushbutton_4;
    bool jinshou;
    bool xianshou;
private:
signals:
    void signal1();//进行人人下棋
    void signal2();//进行人机下棋
    void signal3();//进行机机下棋
    void signal4();//进行联网下棋
};
#endif
