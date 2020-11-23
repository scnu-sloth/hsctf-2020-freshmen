#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
short num[16]={-1,-31753,-17417,-17641,-17577,-18345,-16553,-16617,-16457,-16457,-31215,-2123,-2123,1972,-121,-1};
char map[16][16]={0};
void CreateMap(){
	int i;
	for(i=0;i<0x10;i++){
		unsigned short tmp=num[i];
		int j=1;
		do{
			map[i][0x10-j]=tmp&1;
			tmp>>=1;
		}while(j++&&j<=0x10);
	}
	return;
}
int check(char s[]){
	int len=strlen(s);
	char tmps[100]={0};
	strcpy(tmps,s);
	tmps[5]=0;
	if(strcmp(tmps,"flag{")||s[len-1]!='}') return 0;
	int i;
    int x=0x0D,y=0x00;
	for(i=5;i<len-1;i++){
		switch(s[i]){
			case 0x68:
				y--;
				break;
			case 0x6A:
				x++;
				break;
			case 0x6B:
				x--;
				break;
			case 0x6C:
				y++;
				break;
			default:
                return 0;
		}
		if(!(0<=x<0x10&&0<=y<0x10)||map[x][y]) return 0;
	}
	return 1;
}
int main(){
	char flag[100]={0};
	printf("Please give me the flag:");
	scanf("%100s",flag);
	CreateMap();
	if(strlen(flag)!=0x3B||!check(flag)) printf("\nSorrrrrrrrrry~\n");
	else printf("\nC0ngratu1ations! Your fl4g is r1ght! \n");
	system("pause");
	return 0;
}
