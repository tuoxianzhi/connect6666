#include "Game.h"
#include"mainwindow.h"
#include <utility>
#include <stdlib.h>
#include <time.h>
#include<QDebug>
#include<QApplication>
#include<iostream>
#include<vector>
#include<QTimer>
using namespace std;
const int qipan_size=20;
void Game::getWeight(){
    int weight=0;
    int weight1=0;
    int flag=player?-1:1;
    int flag1=player?1:-1;
    clearscore();
    for(int click_X=0;click_X<qipan_size;click_X++){
        for(int click_Y=0;click_Y<qipan_size;click_Y++){
            if(board[click_X][click_Y]!=0)continue;
            weight=0;
            weight1=0;
            for(int i=-1;i<=1;i++)
                for(int j=-1;j<=1;j++)
                    if(click_X+6*i>=0&&
                       click_X+6*i<qipan_size&&
                       click_Y+6*j>=0&&
                       click_Y+6*j<qipan_size&&
                       click_X+5*i>=0&&
                       click_Y+5*j>=0&&
                       click_X+4*i>=0&&
                       click_Y+4*j>=0&&
                       click_X+3*i>=0&&
                       click_Y+3*j>=0&&
                       click_X+2*i>=0&&
                       click_Y+2*j>=0&&
                       click_X+i>=0&&
                       click_Y+j>=0&&
                       click_X+5*i<qipan_size&&
                       click_Y+5*j<qipan_size&&
                       click_X+4*i<qipan_size&&
                       click_Y+4*j<qipan_size&&
                       click_X+3*i<qipan_size&&
                       click_Y+3*j<qipan_size&&
                       click_X+2*i<qipan_size&&
                       click_Y+2*j<qipan_size&&
                       click_X+i<qipan_size&&
                       click_Y+j<qipan_size&&
                       board[click_X+i*1][click_Y+j*1]==flag&&
                       board[click_X+i*2][click_Y+j*2]==flag&&
                       board[click_X+i*3][click_Y+j*3]==flag&&
                       board[click_X+i*4][click_Y+j*4]==flag&&
                       board[click_X+i*5][click_Y+j*5]==flag){
                            if(board[click_X+i*6][click_Y+j*6]==0)weight+=305;
                            if(board[click_X+i*6][click_Y+j*6]==flag1)weight+=205;
                    }
                    else if(click_X+5*i>=0&&
                            click_Y+5*j>=0&&
                            click_X+4*i>=0&&
                            click_Y+4*j>=0&&
                            click_X+3*i>=0&&
                            click_Y+3*j>=0&&
                            click_X+2*i>=0&&
                            click_Y+2*j>=0&&
                            click_X+i>=0&&
                            click_Y+j>=0&&
                            click_X+5*i<qipan_size&&
                            click_Y+5*j<qipan_size&&
                            click_X+4*i<qipan_size&&
                            click_Y+4*j<qipan_size&&
                            click_X+3*i<qipan_size&&
                            click_Y+3*j<qipan_size&&
                            click_X+2*i<qipan_size&&
                            click_Y+2*j<qipan_size&&
                            click_X+i<qipan_size&&
                            click_Y+j<qipan_size&&
                            board[click_X+i*1][click_Y+j*1]==flag&&
                            board[click_X+i*2][click_Y+j*2]==flag&&
                            board[click_X+i*3][click_Y+j*3]==flag&&
                            board[click_X+i*4][click_Y+j*4]==flag){
                                if(board[click_X+i*5][click_Y+j*5]==0)weight+=130;
                                if(board[click_X+i*5][click_Y+j*5]==flag1)weight+=155;
                    }
                    else if(click_X+4*i>=0&&
                            click_Y+4*j>=0&&
                            click_X+3*i>=0&&
                            click_Y+3*j>=0&&
                            click_X+2*i>=0&&
                            click_Y+2*j>=0&&
                            click_X+i>=0&&
                            click_Y+j>=0&&
                            click_X+4*i<qipan_size&&
                            click_Y+4*j<qipan_size&&
                            click_X+3*i<qipan_size&&
                            click_Y+3*j<qipan_size&&
                            click_X+2*i<qipan_size&&
                            click_Y+2*j<qipan_size&&
                            click_X+i<qipan_size&&
                            click_Y+j<qipan_size&&
                            board[click_X+i*1][click_Y+j*1]==flag&&
                            board[click_X+i*2][click_Y+j*2]==flag&&
                            board[click_X+i*3][click_Y+j*3]==flag){
                                if(board[click_X+i*4][click_Y+j*4]==0)weight+=155;
                                if(board[click_X+i*4][click_Y+j*4]==flag1)weight+=80;
                            }
                    else if(click_X+3*i>=0&&
                            click_Y+3*j>=0&&
                            click_X+2*i>=0&&
                            click_Y+2*j>=0&&
                            click_X+i>=0&&
                            click_Y+j>=0&&
                            click_X+3*i<qipan_size&&
                            click_Y+3*j<qipan_size&&
                            click_X+2*i<qipan_size&&
                            click_Y+2*j<qipan_size&&
                            click_X+i<qipan_size&&
                            click_Y+j<qipan_size&&
                            board[click_X+i*1][click_Y+j*1]==flag&&
                            board[click_X+i*2][click_Y+j*2]==flag){
                                if(board[click_X+i*3][click_Y+j*3]==0)weight+=105;
                                if(board[click_X+i*3][click_Y+j*3]==flag1)weight+=55;
                            }
                    else if(click_X+1*i>=0&&click_X+1*i<qipan_size&&click_Y+1*j>=0&&click_Y+j*1<qipan_size&&board[click_X+1*i][click_Y+1*j]==flag)weight+=20;
                    else weight+=10;
                    for(int i=-1;i<=1;i++)
                        for(int j=-1;j<=1;j++)
                            if(click_X+6*i>=0&&
                               click_X+6*i<qipan_size&&
                               click_Y+6*j>=0&&
                               click_Y+6*j<qipan_size&&
                               click_X+5*i>=0&&
                               click_Y+5*j>=0&&
                               click_X+4*i>=0&&
                               click_Y+4*j>=0&&
                               click_X+3*i>=0&&
                               click_Y+3*j>=0&&
                               click_X+2*i>=0&&
                               click_Y+2*j>=0&&
                               click_X+i>=0&&
                               click_Y+j>=0&&
                               click_X+5*i<qipan_size&&
                               click_Y+5*j<qipan_size&&
                               click_X+4*i<qipan_size&&
                               click_Y+4*j<qipan_size&&
                               click_X+3*i<qipan_size&&
                               click_Y+3*j<qipan_size&&
                               click_X+2*i<qipan_size&&
                               click_Y+2*j<qipan_size&&
                               click_X+i<qipan_size&&
                               click_Y+j<qipan_size&&
                               board[click_X+i*1][click_Y+j*1]==flag1&&
                               board[click_X+i*2][click_Y+j*2]==flag1&&
                               board[click_X+i*3][click_Y+j*3]==flag1&&
                               board[click_X+i*4][click_Y+j*4]==flag1&&
                               board[click_X+i*5][click_Y+j*5]==flag1){
                                    if(board[click_X+i*6][click_Y+j*6]==0)weight+=305;
                                    if(board[click_X+i*6][click_Y+j*6]==flag)weight+=205;
                            }
                            else if(click_X+5*i>=0&&
                                    click_Y+5*j>=0&&
                                    click_X+4*i>=0&&
                                    click_Y+4*j>=0&&
                                    click_X+3*i>=0&&
                                    click_Y+3*j>=0&&
                                    click_X+2*i>=0&&
                                    click_Y+2*j>=0&&
                                    click_X+i>=0&&
                                    click_Y+j>=0&&
                                    click_X+5*i<qipan_size&&
                                    click_Y+5*j<qipan_size&&
                                    click_X+4*i<qipan_size&&
                                    click_Y+4*j<qipan_size&&
                                    click_X+3*i<qipan_size&&
                                    click_Y+3*j<qipan_size&&
                                    click_X+2*i<qipan_size&&
                                    click_Y+2*j<qipan_size&&
                                    click_X+i<qipan_size&&
                                    click_Y+j<qipan_size&&
                                    board[click_X+i*1][click_Y+j*1]==flag1&&
                                    board[click_X+i*2][click_Y+j*2]==flag1&&
                                    board[click_X+i*3][click_Y+j*3]==flag1&&
                                    board[click_X+i*4][click_Y+j*4]==flag1){
                                        if(board[click_X+i*5][click_Y+j*5]==0)weight+=130;
                                        if(board[click_X+i*5][click_Y+j*5]==flag)weight+=155;
                            }
                            else if(click_X+4*i>=0&&
                                    click_Y+4*j>=0&&
                                    click_X+3*i>=0&&
                                    click_Y+3*j>=0&&
                                    click_X+2*i>=0&&
                                    click_Y+2*j>=0&&
                                    click_X+i>=0&&
                                    click_Y+j>=0&&
                                    click_X+4*i<qipan_size&&
                                    click_Y+4*j<qipan_size&&
                                    click_X+3*i<qipan_size&&
                                    click_Y+3*j<qipan_size&&
                                    click_X+2*i<qipan_size&&
                                    click_Y+2*j<qipan_size&&
                                    click_X+i<qipan_size&&
                                    click_Y+j<qipan_size&&
                                    board[click_X+i*1][click_Y+j*1]==flag1&&
                                    board[click_X+i*2][click_Y+j*2]==flag1&&
                                    board[click_X+i*3][click_Y+j*3]==flag1){
                                        if(board[click_X+i*4][click_Y+j*4]==0)weight+=155;
                                        if(board[click_X+i*4][click_Y+j*4]==flag)weight+=80;
                                    }
                            else if(click_X+3*i>=0&&
                                    click_Y+3*j>=0&&
                                    click_X+2*i>=0&&
                                    click_Y+2*j>=0&&
                                    click_X+i>=0&&
                                    click_Y+j>=0&&
                                    click_X+3*i<qipan_size&&
                                    click_Y+3*j<qipan_size&&
                                    click_X+2*i<qipan_size&&
                                    click_Y+2*j<qipan_size&&
                                    click_X+i<qipan_size&&
                                    click_Y+j<qipan_size&&
                                    board[click_X+i*1][click_Y+j*1]==flag1&&
                                    board[click_X+i*2][click_Y+j*2]==flag1){
                                        if(board[click_X+i*3][click_Y+j*3]==0)weight+=105;
                                        if(board[click_X+i*3][click_Y+j*3]==flag)weight+=55;
                                    }
                            else if(click_X+1*i>=0&&click_X+1*i<qipan_size&&click_Y+1*j>=0&&click_Y+j*1<qipan_size&&board[click_X+1*i][click_Y+1*j]==flag1)weight+=20;
                            else weight+=10;
            score[click_X][click_Y]=weight>weight1?weight:weight1;
        }
    }
}
Game::Game(){black=1;white=-1;state=0;xianshou=true;}
void Game::startgame(char type){clear();player=true;if(type==2||type==3)clearscore();}
void Game::clear(){for(int i=0;i<qipan_size;i++)for(int j=0;j<qipan_size;j++)board[i][j]=0;}
void Game::clearscore(){for(int i=0;i<qipan_size;i++)for(int j=0;j<qipan_size;j++)score[i][j]=0;}
void Game::updateqipan(int x,int y){if(player)board[x][y]=1;else board[x][y]=-1; player=!player;}
void Game::startgame1(){player=false;clearscore();}
void Game::AIcaozuo(int &click_X,int &click_Y){
    getWeight();
    int maxScore = 0;
    vector<pair<int, int>> maxPoints;
    for (int row = 0; row < qipan_size; row++)
        for (int col = 0; col < qipan_size; col++){
            if (board[row][col] == 0){
                if (score[row][col] > maxScore){
                    maxPoints.clear();
                    maxScore = score[row][col];
                    maxPoints.push_back(make_pair(row, col));
                }
                else if (score[row][col] == maxScore)maxPoints.push_back(make_pair(row, col));
            }
        }
    srand((unsigned)time(0));
    int index=rand()%maxPoints.size();
    pair<int, int> pointPair = maxPoints.at(index);
    click_X = pointPair.first;
    click_Y = pointPair.second;
    updateqipan(click_X,click_Y);
}
bool Game::isWin(int click_X,int click_Y){
    for (int i =0;i<6;i++)
         if (click_Y-i>=0&&click_Y-i+5<qipan_size&&
            board[click_X][click_Y-i]==board[click_X][click_Y-i+1]&&
            board[click_X][click_Y-i]==board[click_X][click_Y-i+2]&&
            board[click_X][click_Y-i]==board[click_X][click_Y-i+3]&&
            board[click_X][click_Y-i]==board[click_X][click_Y-i+4]&&
            board[click_X][click_Y-i]==board[click_X][click_Y-i+5])return true;
         else if(click_X-i>=0&&click_X-i+5<qipan_size&&
             board[click_X-i][click_Y]==board[click_X-i+1][click_Y] &&
             board[click_X-i][click_Y]==board[click_X-i+2][click_Y] &&
             board[click_X-i][click_Y]==board[click_X-i+3][click_Y] &&
             board[click_X-i][click_Y]==board[click_X-i+4][click_Y]&&
             board[click_X-i][click_Y]==board[click_X-i+5][click_Y])return true;
         else if(click_X+i<qipan_size&&click_X+i-5>=0&&click_Y-i>=0&&click_Y-i+5<qipan_size&&
                 board[click_X+i][click_Y-i]==board[click_X+i-1][click_Y-i+1]&&
                 board[click_X+i][click_Y-i]==board[click_X+i-2][click_Y-i+2]&&
                 board[click_X+i][click_Y-i]==board[click_X+i-3][click_Y-i+3]&&
                 board[click_X+i][click_Y-i]==board[click_X+i-4][click_Y-i+4]&&
                 board[click_X+i][click_Y-i]==board[click_X+i-5][click_Y-i+5])return true;
         else if(click_X-i>=0&&click_X-i+5<qipan_size&&click_Y-i>=0&&click_Y-i+5<qipan_size&&
                  board[click_X-i][click_Y-i]==board[click_X-i+1][click_Y-i+1]&&
                  board[click_X-i][click_Y-i]==board[click_X-i+2][click_Y-i+2]&&
                  board[click_X-i][click_Y-i]==board[click_X-i+3][click_Y-i+3]&&
                  board[click_X-i][click_Y-i]==board[click_X-i+4][click_Y-i+4]&&
                  board[click_X-i][click_Y-i]==board[click_X-i+5][click_Y-i+5])return true;
    return false;
}
bool Game::isHeQi(){
    for(int i=0;i<qipan_size;i++)
        for(int j=0;j<qipan_size;j++)
            if(board[i][j]==0)return false;
    return true;
}
bool Game::isjinshou(int x,int y){
    int num=0,k=0;
    k=0;
    for(int i=0;i<6;i++)
        if(y-i>=0){
            if(board[x][y-i]==1) k++;
            else if(board[x][y-i]==-1)break;
        }
        else break;
    if(k>=4)num++;
    if(num>=2)return true;
    k=0;
    for(int i=0;i<6;i++)
        if(y+i<qipan_size){
            if(board[x][y+i]==1)k++;
            else if(board[x][y+i]==-1)break;
        }
        else break;
    if(k>=4) num++;
    k=0;
    if(num>=2)return true;
    for(int i=0;i<6;i++)
        if(x+i<qipan_size){
            if(board[x+i][y]==1) k++;
            else if(board[x+i][y]==-1) break;
        }
        else break;
    if(k>=4)num++;
    if(num>=2)return true;
    k=0;
    for(int i=0;i<6;i++)
        if(x-i>=0&&y-i>=0){
            if(board[x-i][y-i]==1)k++;
            else if(board[x-i][y-i]==-1)break;
        }
        else break;
    if(k>=4)num++;
    if(num>=2)return true;
    k=0;
    for(int i=0;i<6;i++)
        if(x-i>=0){
            if(board[x-i][y]==1)k++;
            else if(board[x-i][y]==white)break;
        }
        else break;
    if(k>=4)num++;
    if(num>=2) return true;
    k=0;
    for(int i=0;i<6;i++)
        if(x-i>=0&&y+i<qipan_size){
            if(board[x-i][y+i]==1)k++;
            else if(board[x-i][y+i]==-1)break;
        }
        else break;
    if(k>=4)num++;
    if(num>=2)return true;
    k=0;
    for(int i=0;i<6;i++)
        if(x+i<qipan_size&&y+i<qipan_size){
            if(board[x+i][y+i]==1)k++;
            else if(board[x+i][y+i]==-1)break;
        }
        else break;
    if(k>=4)num++;
    if(num>=2)return true;
    return false;
    k=0;
    for(int i=0;i<6;i++)
        if(x+i<qipan_size&&y-i>=0){
            if(board[x+i][y-i]==1)k++;
            else if(board[x+i][y-i]==-1) break;
        }
        else break;
    if(k>=4)num++;
    if(num>=2)return true;
}
