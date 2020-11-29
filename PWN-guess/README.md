Makefile：编译用
guess.c：源码
get：答案（太简单了，pwntool都懒上了）

题名：guess
描述：来猜个数吧，猜中就给shell
hints：
1. 溢出

flag：hsctf{Just_UndEEEEE33333eeeeeerF1ooooooooow!}
可动态

\# build
cd ./ctf_xinetd
docker build -t <iname> .
docker run -d -p <pubport>:9999 --name <cname> <iname>

---

简单的数组下溢，题目中对数组的上界做了检测，但没对下界做检测，即可输入负数。



然后题目说只要找到某个东西是1就猜对了，所以只要往下找到某个是1的位置就好了。为了保证一定有这样的位置，出题人（我）还故意造了个猜对时chance++，即chance可以一直保持为1，而chance的位置是-7，所以一直输-7就可以了。