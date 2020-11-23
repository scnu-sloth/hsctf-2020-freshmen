import libnum
from Crypto.Util import number
from secret import flag

size = 2048
p = number.getPrime(2048)
q = number.getPrime(2048)
m = libnum.s2n(flag)
n = p*q
e = 65537
c = pow(m, e, n)

print(p)
print(q)
print(c)

