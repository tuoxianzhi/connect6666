#ifndef ZHUYE_H
#define ZHUYE_H
#include<QWidget>
#include<QPushButton>
class zhuye : public QWidget{
    Q_OBJECT
public:
    explicit zhuye(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    QPushButton *pushbutton;
    QPushButton *pushbutton_1;
    QPushButton *pushbutton_2;
    QPushButton *pushbutton_3;
    QPushButton *pushbutton_4;
    bool jinshou;
    bool xianshou;
private:
signals:
    void signal1();
    void signal2();
    void signal3();
    void signal4();
};
#endif
