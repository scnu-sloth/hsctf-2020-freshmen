#include "mywindows.h"
//<>引入系统头文件，""自己写的头文件
HANDLE handle;

void initHandle()
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();
}

void setColor(int color)
{
    SetConsoleTextAttribute(handle,color);
}

void setPos(int x,int y)
{
    COORD coord = {x*2,y};      //一个汉字为两个字符
    SetConsoleCursorPosition(handle,coord);
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;   //设置光标是否可见
    info.dwSize = 1;    //光标宽度(1 - 100)
    SetConsoleCursorInfo(handle,&info);
}