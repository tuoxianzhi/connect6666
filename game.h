#ifndef GAME_H
#define GAME_H
#include<QWidget>
#include<QPushButton>
class Game:public QWidget{
    Q_OBJECT
public:
    Game();
    char typeofgame;
    int state;
    bool player;
    void clear();
    bool isWin(int x,int y);
    bool isHeQi();
    void getWeight();
    void startgame1();
    void startgame(char type);
    bool isjinshou(int x,int y);
    void updateqipan(int x, int y);
    int board[21][21];
    int score[21][21];
    void clearscore();
    int white,black;
    void AIcaozuo(int &clickX,int &click_Y);
    bool xianshou;
};
#endif
