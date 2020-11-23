Makefile：编译用
guess.c：源码
get：答案（太简单了，pwntool都懒上了）

题名：guess
描述：来猜个数吧，猜中就给shell
hints：
1. 溢出

flag：hsctf{Just_UndEEEEE33333eeeeeerF1ooooooooow!}
可动态

# build
cd ./ctf_xinetd
docker build -t <iname> .
docker run -d -p <pubport>:9999 --name <cname> <iname>