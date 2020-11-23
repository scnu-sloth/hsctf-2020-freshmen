#ifndef MYWINDOWS_H_INCLUDED
#define MYWINDOWS_H_INCLUDED
//避免重复

/*系统调用模块*/
#include <windows.h>

//函数声明
//初始化句柄
void initHandle();

//设置颜色
void setColor(int color);

//设置光标位置
void setPos(int x,int y);

//隐藏光标
void hideCursor();


#endif // MYWINDOWS_H_INCLUDED