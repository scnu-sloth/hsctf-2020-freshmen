#!/usr/bin/env python3
import random
import time
import sys
from map import *
from secret import flag

'''
NOTHING = 0
WALL = 1
BOMB = 2
PIECE = 3
PERSON = 4
HOLE = 5
'''

def randint(start, end):
    m = end - start + 1
    return random.getrandbits(16) % m + start

actions = ['u', 'd', 'l', 'r', '_']
seed = int(time.time())
random.seed(seed)
x = 1
y = 1
px = randint(1, n-2)
py = randint(1, n-2)
while map[px][py] != NOTHING:
    px = randint(1, n-2)
    py = randint(1, n-2)

def dig():
    global map
    global x, y
    global px, py
    if x==px and y==py:
        print(flag)
        sys.exit(0)
    else:
        map[x][y] = HOLE
        print('DONE')

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

    if map[x2][y2]==NOTHING:
        x = x2
        y = y2
        print('OK')
        return True
    elif map[x2][y2]==WALL:
        print('WALL')
        return False
    elif map[x2][y2]==BOMB:
        print('BOMB')
        exit(-1)
    elif map[x2][y2]==HOLE:
        print('HOLE')
        return False
    else:
        print('ERROR')
        exit(-1)

def start():
    while True:
        action = input()[0]
        if action not in actions:
            sys.exit(-1)
        if action=='_':
            dig()
        else:
            move(action)

start()

