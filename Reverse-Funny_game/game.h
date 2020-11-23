#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/**游戏逻辑模块**/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct{
    int x;
    int y;
    int shape;
    int status;
    int color;
}BLOCK;

typedef struct{///游戏退出动画
    int x;
    int y;
    int changeNumber;
}changeNum;
changeNum st[100];

///绘制游戏池边框
void windowPrint(int x,int y);

///游戏初始化
void gameInit();

///打印操作说明
void printInfo();

///打印分数与等级
void printGradeLevel(int num);//num->消除行数

///游戏计时
void gameTime(clock_t start_time);

///打印方块
void printBlock(int x,int y,int shape,int status,int color);

///删除方块
void deleteBlock(int x,int y,int shape,int status);

///产生游戏第一个方块
void startBlock();

///产生下一个方块
void nextBlock();

///拷贝方块
void copyBlock();

///方块下移
///返回值:方块是否到游戏池底部
int downBlock();

///方块左移
void leftBlock();

///方块右移
void rightBlock();

///方块落底
///方块暂停
///方块变形
void changeStatus();
void changeBlock();

///碰撞检测
int crash(int x, int y, int shape, int status);

///作弊键
void superAction(); //更换形状

///保存方块
void save();

///刷新游戏池
void updateGame();

///暂停
void pause();

///方块落底
void bottomBlock();

///消行检测
void lineClear();

///消行下移
void lineDown(int line);

///游戏结束动画
void printOver();

///重新开始提示
void printFinish();

///重新开始游戏
void againGame();

///打印开始界面
void printStart(int x,int y);

///清除开始动画
void deleteStart(int x,int y);

///动画效果
void printAnimation();

///难度提升
void upLevel();

///音乐控制
void Backmusic();

///绘画
void photoPrint();

///游戏退出动画
void outAnimation();

#endif // GAME_H_INCLUDED