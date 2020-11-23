// flag{H4vE_gr3aT_7eA_Hah}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ignoreMe(unsigned char *a,int len){
    int i;
    for(i=0;i<len;i++) *(a+i)^=0x56;
    return;
}
void encrypt_0v0(unsigned int * v, unsigned int * k){
    int i;
    unsigned int v0=v[0],v1=v[1],sum=0,delta=0x9e3779b9;
    for(i=0;i<32;i++){
        sum+=delta;
        v0+=((v1<<4)+k[0])^(v1+sum)^((v1>>5)+k[1]);
        v1+=((v0<<4)+k[2])^(v0+sum)^((v0>>5)+k[3]);
    }
    v[0]=v0;
    v[1]=v1;
    return;
}
int main(){
    char flag[25]={0},dst[25]={-88,10,-28,-29,19,92,-6,8,13,92,-31,-112,37,18,118,54,81,16,-60,17,-10,-40,-8,-126};
    int i,key[4]={0x33221100,0x77665544,0xBBAA9988,0xFFEEDDCC};
    unsigned int * p_int=(unsigned int*)flag;
    ignoreMe((unsigned char *)encrypt_0v0,189);
    while(1){
        printf("Can you get me? ><\n");
        scanf("%25s",flag);
        if(strlen(flag)!=24){
            printf("Think twice?\n");
            printf("-=-=-=-=-=-=-=-=-=-=\n");
        }
        else break;
    }
    for(i=0;i<6;i+=2) encrypt_0v0(&p_int[i],(unsigned int*)key);
    if(!strcmp(flag,dst)) printf("\nNow, I am yours. 0v0\n");
    else printf("\nThink twice and think twice? 0x0\n");
    system("pause");
    return 0;
}