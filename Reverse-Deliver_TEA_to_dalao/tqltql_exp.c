// flag{H4vE_gr3aT_7eA_Hah}

#include <stdio.h>
char flag[]={-88,10,-28,-29,19,92,-6,8,13,92,-31,-112,37,18,118,54,81,16,-60,17,-10,-40,-8,-126};
int key[]={0x33221100,0x77665544,0xBBAA9988,0xFFEEDDCC};
void decrypt(unsigned int * v, unsigned int * k){
    int i;
    unsigned int v0=v[0],v1=v[1],sum=0,delta=0x9e3779b9;
    sum=delta*32;
    for(i=0;i<32;i++){
        v1-=((v0<<4)+k[2])^(v0+sum)^((v0>>5)+k[3]);
        v0-=((v1<<4)+k[0])^(v1+sum)^((v1>>5)+k[1]);
        sum-=delta;
    }
    v[0]=v0;
    v[1]=v1;
    return;
}
int main(){
    int i;
    unsigned int * p_int=(unsigned int*)flag;
    for(i=0;i<6;i+=2) decrypt(&p_int[i],(unsigned int*)key);
    printf("%s",flag);
    return 0;
}