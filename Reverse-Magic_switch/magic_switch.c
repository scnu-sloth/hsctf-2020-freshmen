//flag： flag{Re_is_reaIIy_e4sy_and_int3rest1ng}

#include <stdio.h>
#include <stdlib.h>
int state[8]={0};
char btn[8][2][50]={"|--1--- B --------------- =) -------|\n\0","|--1---------------- (*^-^*) -------|\n\0",
                    "|--2--- B --------------- :/ -------|\n\0","|--2---------------- <(_ _)> -------|\n\0",
                    "|--3--- B --------------- =D -------|\n\0","|--3---------------- q(^o^q) -------|\n\0",
                    "|--4--- B --------------- :( -------|\n\0","|--4---------------- (oT^T)o -------|\n\0",
                    "|--5--- B -------------- 0v0 -------|\n\0","|--5--------------- (~>w<)~* -------|\n\0",
                    "|--6--- B -------------- -v- -------|\n\0","|--6---------------- ~(\'v\'~) -------|\n\0",
                    "|--7--- B -------------- QvQ -------|\n\0","|--7---------------- (*/v\\*) -------|\n",
                    "|--8--- B -------------- =v= -------|\n\0","|--8-------------- o(=OwO=)y -------|\n"};
char flag[33]={0},fake_flag[33]={72, 97, 104, 97, 104, 97, 104, 97, 104, 97, 104, 97, 104, 95, 84, 104, 49, 115, 95, 105, 115, 95, 97, 95, 102, 52, 107, 101, 95, 102, 49, 97, 103};
void menu(){
	int i; 
    printf("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n");
    for(i=0;i<8;i++) printf("%s",btn[i][state[i]]);
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    return;
}
void secret(){
    char src[33]={14,16,35,28,15,42,14,16,29,60,53,12,35,46,116,15,92,56,42,19,3,20,28,37,6,19,13,20,56,6,20,27,20};
    int i;
    for(i=0;i<33;i++){
        flag[i]^=src[i];
        flag[i]^=fake_flag[i];
        flag[i]^=20;
    }
    return;
}
int main(){
    system("clear");
    printf("Play with the MAGIC SWITCH!\n");
    printf("N is the serial number of these switches. \n");
    printf("At first, all the switches were off. \n");
    printf("Now you can input N to change its state. \n");
    printf("But, \n");
    printf("you should pay attention to one thing that \n");
    printf("if you change the state of Nth, \n");
    printf("the state of (N-1)th and (N+1)th will be changed too. \n");
    printf("When all switches are on, the flag will appear. \n");
    printf("GOOD LUCK!\n");
    while(1){
        int n,i;
        int flg=1;
        for(i=0;i<8;i++){
            if(!state[i]){
                flg=0;
                break;
            }
        }
        if(flg){
            secret();
            menu();
            printf("We11 d0ne! The flag is: flag{%s} >v<\n",flag);
            break;
        }
        while(1){
            menu();
            printf("Now, please input the N(0-8, 0 to restart). \n");
            printf("n=");
            scanf("%d",&n);
            if(0<=n&&n<=8) break;
            system("clear");
            printf("Do you sure you've input a right number? XD \n\n");
        }
        if(!n){
            system("clear");
            for(i=0;i<8;i++) state[i]=0;
            continue;
        }
        n--;
        int tmp[3]={n-1>=0? n-1:7,n,(n+1)%8};
        for(i=0;i<3;i++) state[tmp[i]]^=1;
        system("clear");
    }
    return 0;
}
