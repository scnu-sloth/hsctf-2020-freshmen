#! -*- encoding:utf8 -*-
from __future__ import print_function
from map import map
# support you leak the map
from pwn import *
import time
import os

n = 16
NOTHING = 0
WALL = 1
BOMB = 2
PIECE = 3
PERSON = 4
HOLE = 5
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

actions = ['u', 'd', 'l', 'r', '_']
change = {'w':'u', 's':'d', 'a':'l', 'd':'r', ' ':'_'}

t1 = int(time.time())
r = remote('127.0.0.1', 9006)
t2 = int(time.time())
if t1!=t2:
    print('Try again!')
    r.close()
    exit(-1)

seed = t1
print('[LEAK] seed -> '+str(seed))
random.seed(seed)

def randint(start, end):
    m = end - start + 1
    return random.getrandbits(16) % m + start

px = randint(1, n-2)
py = randint(1, n-2)
while map[px][py] != NOTHING:
    px = randint(1, n-2)
    py = randint(1, n-2)
print('[LEAK] piece -> '+str(px)+', '+str(py))

def move(c):
    global x, y
    x2, y2 = x, y

    if c == 'u':
        y2 = y-1
    elif c == 'd':
        y2 = y+1
    elif c == 'l':
        x2 = x-1
    elif c == 'r':
        x2 = x+1
    else:
        print('ERROR')
        exit(-1)
    return x2, y2

def debug():
    global map
    per = map[x][y]
    pie = map[px][py]
    map[x][y] = PERSON
    map[px][py] = PIECE
    printMap(map)
    map[x][y] = per
    map[px][py] = pie

x, y = 1, 1
while True:
    dire = raw_input()[0]
    dire = change[dire]
    os.system("clear")
    r.sendline(dire)
    result = r.recvline()
    print('[DEBUG] -> '+result)
    if dire!='_':
        x2, y2 = move(dire)
        if 'OK' in result:
            x, y = x2, y2
    else:
        if 'DONE' in result:
            map[x][y] = HOLE
    debug()


# 他说这代码是乱写的，
# 这可不是乱写的啊!
