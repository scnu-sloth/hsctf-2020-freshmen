# flag{tq1_0v0_y0u_nnust_b3_A_d4lao}
import dis

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
    a=(a+2*c)*3+4*c #13
    b=b+2*a+4*c+c #25
    return s[b:a:-1]+s[:b:-1]+s[:a+1]

print("Disassembly of main:")
dis.dis(main)
print('\n\n')
print("Disassembly of foo1:")
dis.dis(foo1)
print('\n\n')
print("Disassembly of foo2:")
dis.dis(foo2)
print('\n\n')
print("Disassembly of foo3:")
dis.dis(foo3)

# main()