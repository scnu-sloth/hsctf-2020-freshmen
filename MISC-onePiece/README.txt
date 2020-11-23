题目文件：game.py
运行：ncat -vc ./game.py -kl 127.0.0.1 9006

题名：One Piece
描述：去找吧，我把flag放在那里了！
hints:
1. 地图是不变的啊
2. 随机是真的随机？
3. 实在不行一笔画总玩过吧？

flag: HSCTF{D1d_u_g0t_th3_53ed?}
改secret可动态

# build
cd ./build
docker build -t <iname> .
docker run -d -p <pubport>:9999 --name <cname> <iname>