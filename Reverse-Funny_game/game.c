#include "game.h"
#include "data.h"
#include "mywindows.h"
#include <conio.h>

int grade = 0;      ///分数
int level = 1;      ///等级

#include <mmsystem.h>///必须放在mywindows.h后面
int record_01=0,record_02=0,Max,isInvisibility =0;
double speed = 0.6;

BLOCK cur_block;    ///当前方块
BLOCK next_block;   ///下一个方块


void windowPrint(int x,int y)
{
    int i,j;
    for(i=0;i<27;i++)
    {
        for(j=0;j<26;j++)
        {
            if(windowShape[i][j] == 1)
            {
                setColor(0x90);
                setPos(x+j,y+i);
                printf("%2s","");
            }
        }
    }
}

void printInfo()
{
    setColor(0x0a);

    setPos(31,9);
    printf("操作规则:");
    setPos(32,11);
    printf("按 a 或 A 左移");
    setPos(32,12);
    printf("按 d 或 D 右移");
    setPos(32,13);
    printf("按 w 或 W 变形");
    setPos(32,14);
    printf("按 s 或 S 下移");
    setPos(32,15);
    printf("按 回车 直接下落");
    setPos(32,16);
    printf("按 空格 暂停");

    setColor(0x0b);
    setPos(32,18);
    printf("按 G/g 试试？？");

}

void printGradeLevel(int num)
{
    switch(num)///一次消行越多，分数越多
    {
        case 0:
        break;
        case 1:
        grade +=10; record_01= 1; break;
        case 2:
        grade +=30; record_01= 2;break;
        case 3:
        grade +=50; record_01= 3;break;
        case 4:
        grade +=80; record_01= 4; break;
    }
    if(grade < 100 && speed!=0.1)
        level=1;
    else if(grade >= 100 && grade < 200 && speed!=0.1)
        level=2;
    else if(grade >= 200 && grade < 300 && speed!=0.1)
        level=3;
    else if(grade >= 300 && grade < 500 && speed!=0.1)
        level=4;
    else if(grade >= 500 && grade < 900 && speed!=0.1)
        level=5;
    else if(speed == 0.1)
        level=9;

    if(grade>Max){
        Max=grade;
    }

    setColor(0x0E);
    setPos(6,3);
    printf("分数: %d",grade);

    setPos(6,4);
    printf("等级: %d",level);

    setPos(4,7);
    printf("一次消除行数：%d",record_01);

    setPos(5,6);
    printf("总消除行数：%d",record_02);

    setPos(6,5);
    printf("最高分：%d",Max);

    setColor(0x0B);
    setPos(3,2);
    printf("* * * * * * * * * *");

    setColor(0x0B);
    setPos(3,8);
    printf("* * * * * * * * * *");

    setColor(0x0B);
    setPos(3,4);
    printf("*\n");
    setPos(3,5);
    printf("*\n");
    setPos(3,3);
    printf("*\n");
    setPos(12,3);
    printf("*\n");
    setPos(3,6);
    printf("*\n");
    setColor(0x0B);
    setPos(3,7);
    printf("*\n");
    setColor(0x0B);
    setPos(12,6);
    printf("*\n");
    setColor(0x0B);
    setPos(12,7);
    printf("*\n");
    setPos(12,4);
    printf("*\n");
    setPos(12,5);
    printf("*\n");
    setPos(12,6);
    printf("*\n");
}

void gameTime(clock_t start_time)
{
    setColor(0x7d);
    setPos(5,12);
    printf("游戏已运行 %ld s",(clock()-start_time)/CLOCKS_PER_SEC);

    setColor(0x0f);
    setPos(3,10);
    printf("○ ○ ○ ○ ○ ○ ○");
    setColor(0x0f);
    setPos(3,14);
    printf("○ ○ ○ ○ ○ ○ ○");
    setPos(3,12);
    printf("○ ");
    setPos(12,12);
    printf("○ ");
}

void printBlock(int x,int y,int shape,int status,int color)
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(block[shape][status][i][j] == 1)
            {
                setColor(color);
                setPos(x+j,y+i);
                printf("■");
            }
        }
    }
}

void deleteBlock(int x,int y,int shape,int status)
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(block[shape][status][i][j] == 1)
            {
                setPos(x+j,y+i);
                printf("  ");
            }
        }
    }
}

void startBlock()
{
    ///第一个方块:形状/形态/颜色->随机 位置固定
    ///初始化cur_block
    ///设置随机数种子(时间水远不一样)
    srand((unsigned)time(NULL));
    cur_block.x = 22;
    cur_block.y = 1;
    cur_block.shape = rand()%7;
    cur_block.status = rand()%4;
    cur_block.color = rand()%0x10;  ///0x00-0x0f
    ///如果随机产生的颜色是黑色,把颜色设置为白色
    if(cur_block.color == 0x00)
    {
        cur_block.color = 0x0f;
    }
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
}

void nextBlock()
{
    ///形状/形态/颜色->随机 位置->固定
    ///初始化next_block
    ///删除上一个
    setColor(0x04);
    setPos(31,1);
    printf("NEXT:");
    deleteBlock(next_block.x,next_block.y,next_block.shape,next_block.status);
    next_block.x = 34;
    next_block.y = 2;
    next_block.shape = rand()%7;
    next_block.status = rand()%4;
    next_block.color = rand()%0x10;
    if(next_block.color == 0x00)
    {
        next_block.color = 0x0f;
    }
    printBlock(next_block.x,next_block.y,next_block.shape,next_block.status,next_block.color);
}

void copyBlock()
{
    ///当前方块=下一个方块,并产生新的"下一个方块"
    cur_block = next_block;
    cur_block.x = 22;
    cur_block.y = 1;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
    nextBlock();
}

int downBlock()
{
    ///原理:删除正在显示的方块,纵坐标+1,重新打印
    if(crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) == -1)
    {
        ///发生碰撞:方块落到游戏池底部
        ///产生新的方块:下一个方块的值->当前正在下落的方块,重新产生下一个方块
        ///保存方块，检测消行，打印游戏池，产生新方块
        save();
        lineClear();
        updateGame();
        copyBlock();
        return -1;
    }else if(crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) == -2)
    {
        ///游戏结束
        return -2;
    }else{
        deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
        cur_block.y +=1;
        printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
        return 0;
    }
}

void leftBlock()
{
    if(crash(cur_block.x-1,cur_block.y,cur_block.shape,cur_block.status) == -1)
    {
        return;
    }
    deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
    cur_block.x -= 1;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
}

void rightBlock()
{
    if(crash(cur_block.x+1,cur_block.y,cur_block.shape,cur_block.status) == -1)
    {
        return;
    }
    deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
    cur_block.x +=1;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
}

void changeStatus()//自己写的
{
   deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
   int inset = cur_block.status;
   if(cur_block.shape == 0 || cur_block.shape == 4)
       cur_block.status = rand()%2;
   else
       cur_block.status = rand()%4;
   if(cur_block.status != inset){
       printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
   }
   else
    changeStatus();
}

void changeBlock()
{
    ///通过数组下标+1，获得下一个形态，下标[0-3]
    if(crash(cur_block.x,cur_block.y,cur_block.shape,(cur_block.status+1)%4) == -1)
    {
        return;
    }
    deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
    cur_block.status = (cur_block.status+1)%4;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
}

void superAction()
{
    if(crash(cur_block.x,cur_block.y,(cur_block.shape+1)%7,cur_block.status) == -1)
    {
        return;
    }
    deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
    cur_block.shape = (cur_block.shape+1)%7;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
}
int crash(int x, int y, int shape, int status)
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(block[shape][status][i][j] == 1)
            {
                if(windowShape[i+y][j+x-15] == 1)
                {
                    ///发生碰撞
                    if(cur_block.x == 22 && cur_block.y == 1)
                    {
                        ///方块产生就发生碰撞,游戏结束
                        return -2;
                    }
                    ///方块落到游戏池底部，发生碰撞
                    return -1;
                }
            }
        }
    }
    return 0;
}

void save()
{
    ///根据方块在界面上的坐标,把坐标对应到游戏池的下标的位置
    ///方块为1的保存到windowShape数组
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(block[cur_block.shape][cur_block.status][i][j] == 1)
            {
                windowShape[i+cur_block.y][j+cur_block.x-15] = 1;
            }
        }
    }
}

void updateGame()
{
    int i,j;
    for(i=25;i>0;i--)
    {

        for(j=1;j<15;j++)
        {
            if(windowShape[i][j] == 1){
                if(isInvisibility == 1)
                    setColor(0x00);
                else
                    setColor(0x0e);
                setPos(15+j,i);
                printf("■");
            }else{
                setColor(0x00);
                setPos(15+j,i);
                printf("%2s","");
            }
        }
    }
}

void pause()
{
    setColor(0x7d);
    setPos(5,12);
    printf("游 戏 已 暂 停");
    while(1){

        if(getch() == 32)
        {
            break;
        }
    }
}

void bottomBlock()
{
    while(1)
    {
        if(crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) == -1)
        {
            save();
            lineClear();
            updateGame();
            copyBlock();
            return;
        }else if(crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) == -2)
        {
            return;
        }else{
         ++cur_block.y;
     }
 }
}

void lineClear()
{
    ///遍历windowShape，判断是否满行：一行元素相加为14
    int i,j;
    int number = 0;
    for(i=25;i>0;i--)
    {
        int total = 0;
        for(j=1;j<15;j++)
        {

            total += windowShape[i][j];
        }
        if(total == 14)
        {
            lineDown(i);
            i += 1;     ///回归这一行
            ///统计一次消几行
            number += 1;
            record_02++;
        }
    }
    printGradeLevel(number);
    number = record_01;
}

void lineDown(int line)
{
    ///从第line行开始，将i = i-1
    int i,j;
    for(i=line;i>1;i--) ///i>0时下移边界
    {
        for(j=0;j<15;j++)
        {
            windowShape[i][j] = windowShape[i-1][j];
        }
    }
}

void printOver()
{
    if(isInvisibility == 1)
    {
        int i,j;
        for(i=25;i>0;i--)
        {
            for(j=1;j<15;j++)
            {
                if(windowShape[i][j] == 1){
                    setColor(0x0e);
                    setPos(15+j,i);
                    printf("■");
                }else{
                    setColor(0x00);
                    setPos(15+j,i);
                    printf("%2s","");
                }
                Sleep(1);
            }
        }
    }
    int i,j;
    for(i=25;i>0;i--)
    {
        for(j=1;j<15;j++)
        {
            setColor(0x76);
            setPos(j+15,i);
            printf("■");
            Sleep(5);
        }
    }
}

void printFinish()
{
    setColor(0x0d);
    setPos(21,8);
    printf("游戏结束! ");
    setPos(17,9);
    printf("按Y重新开始 ");
    setPos(23,9);
    printf("按N结束游戏 ");

    switch(getch())
    {
        case 'y':
        case 'Y':
        againGame();break;
        case 'n':
        case 'N':
        outAnimation();break;
        default :
        printFinish();break;
    }
}

void againGame()
{
    ///重置分数、等级、游戏池数据->开始游戏
    level = 1;
    grade = 0;
    record_01 = 0;
    isInvisibility = 0;
    speed = 0.6;
    ///重置游戏池
    int i,j;
    for(i=1;i<26;i++){
        for(j=1;j<15;j++)
        {
            windowShape[i][j] = 0;
        }
    }
    system("cls");  ///清屏
    gameInit();
}

void upLevel(){
    if(level==2){
        speed = 0.45;
    }
    else if(level==3){
        speed = 0.4;
    }
    else if(level==4){
        speed = 0.35;
    }
    else if(level==5){
        speed = 0.3;
    }
}
void printStart(int x,int y)
{
    ///随机图案颜色
    int color = rand()%0x10;
    if(color == 0x00){
        color = 0x0f;
    }
    ///绘制图案
    setColor(color);
    setPos(x,y);
    printf("■■■■■  ■■■■■  ■■■■■  ■■■■ ■■■ ■■■■");
    setPos(x,y+1);
    printf("    ■      ■              ■      ■    ■   ■   ■    ■");
    setPos(x,y+2);
    printf("    ■      ■■■■■      ■      ■■■■   ■   ■■■■");
    setPos(x,y+3);
    printf("    ■      ■              ■      ■  ■     ■   ■");
    setPos(x,y+4);
    printf("    ■      ■■■■■      ■      ■    ■   ■   ■");

    setPos(25,16);
    printf("  请选择游戏模式");
    setPos(25,17);
    printf("按 Z/z键普通模式！");
    setPos(25,18);
    printf("按 L/l键地狱模式！");
    setPos(25,19);
    printf("按 K/k键隐形模式！");

    setPos(22,14);
    printf("----------------------------");
    setPos(21,15);
    printf(" /                            \\");
    setPos(21,16);
    printf("/");
    setPos(36,16);
    printf(" \\");
    setPos(20,17);
    printf(" /");
    setPos(36,17);
    printf("  \\");
    setPos(20,18);
    printf(" \\");
    setPos(37,18);
    printf("/");
    setPos(21,19);
    printf("\\");
    setPos(36,19);
    printf(" /");
    setPos(21,20);
    printf(" \\");
    setPos(36,20);
    printf("/");
    setPos(22,21);
    printf("----------------------------");
}

void deleteStart(int x,int y)
{
    int i,j;
    for(i=y;i<=y+4;i++)
    {
        for(j=x;j<=x+33;j++){
            setPos(j,i);
            printf("%2s","");
        }
    }
}

void printAnimation()
{
    clock_t time1,time2;
    time1 = clock();
    int x=5;
    while(1)
    {
        time2= clock();
        if(time2-time1>300)///时间间隔300ms
        {
            time1 = time2;
            deleteStart(x,5);
            printStart(++x,5);
            if(25 == x)
            {
                deleteStart(x,5);
                x=5;
            }
        }
        ///任意键退出
        if(kbhit())
        {
            switch(getch()){
                case 'Z':
                case 'z':
                break;
                case 'l':
                case 'L':
                speed = 0.1;break;
                case 'k':
                case 'K':
                isInvisibility = 1;break;
                default :
                continue;
            }
            break;
        }
    }
    system("cls");
}

void photoPrint()
{
    setPos(0,29);
    setColor(0xb0);
    printf("%120s","");
    setPos(0,28);
    setColor(0xb0);
    printf("%120s","");
    setPos(0,28);


    setPos(47,17);
    setColor(0x01);
    printf("■■■■■");
    setPos(46,18);
    printf("■■■■■■■");
    setPos(45,19);
    printf("■              ■");
    setPos(45,20);
    printf("■              ■");
    setPos(45,21);
    printf("■              ■");
    setPos(46,22);
    printf("■■■■■■■");
    setPos(47,23);
    printf("■■■■■");

    setColor(0x06);
    setPos(46,19);
    printf("■■■■■■■");
    setPos(46,20);
    printf("■■       ■■");
    setPos(46,21);
    printf("■■■■■■■");
    setPos(48,20);
    printf("Cat mat");

    setPos(49,9);
    setColor(0x0f);
    printf("/\\      /\\         |");
    setPos(48,10);
    printf(" /  \\____/  \\      ||");
    setPos(48,11);
    printf("/  0    0    \\____||");
    setPos(48,12);
    printf("\\    /\\      /   |");
    setPos(48,13);
    printf(" \\__________/____|");
    setPos(50,14);
    printf(" ||      ||");
    setPos(50,15);
    printf(" ||      ||");

    setPos(55,26);
    setColor(0x07);
    printf("/  |/|");
    setPos(55,25);
    printf(" / |");
    setPos(55,24);
    printf("  /|");
    setPos(55,27);
    printf("\\  |\\|");
    setPos(56,26);
    printf("0");

    setPos(10,27);
    setColor(0x07);
    printf("/  |");
    setPos(10,26);
    printf(" / |");
    setPos(10,25);
    printf("  /|");

    setPos(6,27);
    setColor(0x07);
    printf("/|");

    setPos(1,24);
    setColor(0x47);
    printf(" 鲨鱼出没！");
    setPos(1,23);
    setColor(0x47);
    printf("   Waring  ");
    setPos(3,25);
    setColor(0x41);
    printf("  ");
    setPos(3,26);
    setColor(0x41);
    printf("  ");
    setPos(3,27);
    setColor(0x41);
    printf("  ");
}

void outAnimation()
{
    system("cls");//先清屏
    hideCursor();
    int i;
    for(i=0;i<100;i++)//设计随机位置，设置数字雨随机数
    {
        st[i].x=rand()%60;
        st[i].y=rand()%26;
        st[i].changeNumber=rand()%2;
    }
    while(1)
    {
        for(i=0;i<100;i++)
        {
            setPos(st[i].x,st[i].y);
            setColor(0x02);
            printf("%d",st[i].changeNumber);
            setPos(st[i].x,st[i].y-5);//设置空格位置
            printf(" ");
            st[i].y++;//动态下落
            st[i].changeNumber=rand()%2;//变数
            if(st[i].y>=24)//设置边界线，达到输出空格
            {
                setPos(st[i].x,st[i].y-1);
                printf(" ");
            }
            if(st[i].y>28)
                st[i].y=rand()%25;
            if(st[i].x>=60)
                st[i].y=rand()%25;
            setPos(st[i].x,st[i].y);
            printf("%d",st[i].changeNumber);
        }
        int color = rand()%0x10;
        if(color == 0x00){
            color = 0x0f;
        }
        setPos(25,4);
        setColor(color);
        printf("游戏结束");
        Sleep(120);
        if(kbhit())
        {
            break;
        }
    }
    exit(0);
}

void getflag(){
    int arr[32]={110, 148, 97, 111, 155, 113, 157, 81, 156, 109, 103, 97, 103, 110, 157, 150, 150, 153, 103, 111, 92, 149, 109, 103, 105, 147, 150, 124, 103, 105, 156, 133};
    char flag[33]={0};
    for(int i=0;i<32;i++){
        flag[i]^=arr[i];
        flag[i]^=20;
        flag[i]-=20;
    }
    int color = rand()%0x10;
    if(color == 0x00){
        color = 0x0f;
    }
    setPos(43,4);
    setColor(color);
    printf("%s",flag); //flag{Qu1te_a_funny_g4me_isnT_it}
    return;
}

void gameInit()
{
    initHandle();
    printAnimation();
    windowPrint(15,0);
    printInfo();
    printGradeLevel(0);
    //photoPrint();

    ///游戏开始时间
    clock_t startTime = clock();

    ///定时器
    clock_t time1,time2;
    time1 = clock();

    startBlock();
    nextBlock();
    while(1){
        upLevel();

        ///检测是否有按键按下
        if(kbhit()){
            switch(getch()){
                case 'w':
                case 'W':
                case 72:
                ///方块变形
                    changeBlock();break;
                case 'a':
                case 'A':
                case 75:
                ///方块左移
                    leftBlock();break;
                case 'd':
                case 'D':
                case 77:
                ///方块右移
                    rightBlock();break;
                case 's':
                case 'S':
                case 80:
                ///方块下移
                    downBlock();break;
                case 32:
                ///暂停
                    pause();break;
                case 13:
                ///方块落底
                    bottomBlock();break;
                case 'g':
                case 'G':
                ///作弊
                    superAction();break;
            }
        }
        time2 = clock();
        ///每0.45秒下落一次
        if(time2 - time1 > speed*CLOCKS_PER_SEC){
            ///游戏计时
            gameTime(startTime);
            if(downBlock() == -2){
                if(grade==2020) getflag();
                break;
            }
            time1 = time2;  ///重新赋值
        }
    }
    printOver();
    printFinish();
}