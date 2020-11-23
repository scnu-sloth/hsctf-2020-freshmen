import libnum
from Crypto.Util import number
from gmpy2 import invert
from secret import flag

size = 2048
m = libnum.s2n(flag)
p = number.getPrime(2048)
q = number.getPrime(2048)
n = p*q
e = number.getPrime(256)
phi = (p-1)*(q-1)
d = invert(e, phi)
dp = d % (p-1)
dq = d % (q-1)
c = pow(m, e, n)

print(p)
print(q)
print(dp)
print(dq)
print(c)

