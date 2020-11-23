import libnum
from Crypto.Util import number
from secret import flag

p = number.getPrime(2048)
q = number.getPrime(2048)
m = libnum.s2n(flag)
n = p*q
e = 65537

c1 = pow(p, e, n)
c2 = pow(q, e, n)
c3 = pow(m, e, n)

print('n='+str(n))
print('c1='+str(c1))
print('c2='+str(c2))
print('c3='+str(c3))

