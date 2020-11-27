# Bytecode

## 题目描述

Python字节码，在线求逆（

## 题目文件

`bytecode.txt`

## Hint

Hint 1: 死磕python字节码，冲！（https://bbs.pediy.com/thread-246683.htm）

## flag

flag{tq1_0v0_y0u_nnust_b3_A_d4lao}

---

## Write up

python字节码人工反编译，在网上能搜到很多死磕字节码的教程（比如hint给的 [死磕python字节码](https://bbs.pediy.com/thread-246683.htm) 或者 [python 字节码死磕](https://www.cnblogs.com/yinguohai/archive/2004/01/13/11158492.html)），最需要的是耐心hhhh。

然后可以逆出源码

```python
def main():
    flag=input("No Flag No Entry <(_^_)>:\n")
    if len(flag)==34 and foo1(foo2(foo3(flag))):
        print("\nAcc3pTed: You g0t iT! :D")
    else:
        print("\nErr0r: Unm4tched str1ng. :/")

def foo1(s):
    arr=[51, 42, 67, 2, 100, 48, 94, 29, 25, 26, 9, 43, 25, 21, 53, 11, 11, 91, 0, 12, 14, 19, 122, 0, 44, 26, 58, 26, 28, 24, 50, 3, 93, 21]
    if s==arr:
        return True
    else:
        return False

def foo2(s):
    arr1=list(map(ord,s))[::-1]
    arr2=[74, 117, 115, 116, 84, 111, 111, 108, 109, 97, 110] #"JustToolman"
    for i in range(len(arr1)):
        arr1[i]^=arr2[i%11]
    return arr1

def foo3(s):
    a=1
    b=-6
    c=len(s)-33
    a=(a+2*c)*3+4*c
    b=b+2*a+4*c+c
    return s[b:a:-1]+s[:b:-1]+s[:a+1]
```

简单逆向，主要的点在字节码反编译部分，只要把源码逆出来就能写出脚本啦，刚好能帮助入门python。

就是切片那一块有一点点坑，注意是前到后不到的就好。

~~本来还有一层加密的，为了降低难度删掉了。~~

```python
arr1=[51, 42, 67, 2, 100, 48, 94, 29, 25, 26, 9, 43, 25, 21, 53, 11, 11, 91, 0, 12, 14, 19, 122, 0, 44, 26, 58, 26, 28, 24, 50, 3, 93, 21]
arr2=[74, 117, 115, 116, 84, 111, 111, 108, 109, 97, 110]
for i in range(len(arr1)):
    arr1[i]^=arr2[i%11]
arr1=list(map(chr,arr1))[::-1]
s=''.join(arr1)
a=13
b=25
flag=s[-a-1:]+s[b-a-1::-1]+s[-a-2:b-a-1:-1]
print(flag)

#flag{tq1_0v0_y0u_nnust_b3_A_d4lao}
```
