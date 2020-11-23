from __future__ import print_function
n = 16
NOTHING = 0
WALL = 1
BOMB = 2
PIECE = 3
PERSON = 4
HOLE = 5

map = [\
[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], \
[1, 0, 0, 0, 0, 1, 2, 0, 0, 0, 1, 1, 0, 0, 2, 1], \
[1, 0, 0, 1, 0, 0, 0, 1, 0, 2, 0, 0, 0, 1, 0, 1], \
[1, 2, 1, 1, 1, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 1], \
[1, 2, 0, 0, 0, 0, 1, 1, 0, 0, 2, 0, 2, 1, 0, 1], \
[1, 0, 2, 0, 1, 0, 1, 0, 0, 2, 0, 2, 0, 0, 0, 1], \
[1, 0, 2, 0, 0, 1, 1, 0, 0, 1, 0, 2, 1, 1, 1, 1], \
[1, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 1], \
[1, 1, 0, 0, 1, 1, 0, 0, 2, 0, 0, 2, 0, 0, 0, 1], \
[1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 1], \
[1, 2, 2, 0, 0, 0, 2, 0, 2, 1, 0, 0, 2, 2, 1, 1], \
[1, 0, 1, 2, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1], \
[1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1], \
[1, 2, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 2, 0, 1], \
[1, 0, 0, 0, 1, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 1], \
[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]  \
]

def printMap(mp):
    for j in range(n):
        for i in range(n):
            if mp[i][j]==0:
                print('\033[37;47mNN\033[0m', end='')
            elif mp[i][j]==1:
                print('\033[34;44mWW\033[0m', end='')
            elif mp[i][j]==2:
                print('\033[36;46mBB\033[0m', end='')
            elif mp[i][j]==3:
                print('\033[33;43mBB\033[0m', end='')
            elif mp[i][j]==4:
                print('\033[35;45mPP\033[0m', end='')
            else:
                print('  ', end='')
        print('')
