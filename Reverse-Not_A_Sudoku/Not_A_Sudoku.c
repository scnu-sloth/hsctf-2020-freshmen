// flag{001111000011111100110001110111111110111111111011111111000011110000001110000111100}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char sudo[2][32]={{4,-1,6,-1,2,3,-1,8,-1,9,-1,8,-1,4,-1,3,-1,4,-1},
                {3,-1,5,-1,2,3,-1,2,3,1,-1,2,4,1,-1,9,-1,8,-1,6,-1,2,-1}};
int C(int x){
    return x==0? 1:9;
}
int check(char s[],int x){
    int pos=0;
    for(int i=0;i<9*C(x^1);i+=C(x^1)){
        for(int j=0;j<9*C(x);j+=C(x)){
            if(s[i+j]=='0') continue;
            int tmp=j;
            while(s[i+j]=='1'&&j<9*C(x)) j+=C(x);
            if(sudo[x][pos]!=(j-tmp)/C(x)) return 0;
            else pos++;
        }
        if(sudo[x][pos]!=-1) return 0;
        else pos++;
    }
    return 1;
}
int main(){
    char input[100]={0};
    printf("Please give me a correct string of numbers(only made up of 0 and 1): \n");
    scanf("%100s",input);
    if(strlen(input)!=81||!check(input,0)||!check(input,1)) printf("Try again. X_X\n");
    else printf("R1ght! H3re it is: flag{%s}. =v=\n",input);
    system("pause");
    return 0;
}