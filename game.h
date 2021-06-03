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
    void clear();//清除棋盘
    bool isWin(int x,int y);//判断输赢
    bool isHeQi();//判断和棋
    void getWeight();//获取棋子权值
    void startgame1();//开始黑方人机游戏
    void startgame(char type);//开始其他游戏
    bool isjinshou(int x,int y);//判断禁手
    void updateqipan(int x, int y);//迭代棋盘
    void renleichaozuo(int x,int  y);//输入人类操作
    void clearscore();//清理分数
    void playEVE(int &clickx,int &click_Y);//机机对弈
    void AIcaozuo(int &clickX,int &click_Y);//模拟ai操作
    int board[21][21];
    int score[21][21];
    int white,black;
    bool xianshou;
};
#endif
