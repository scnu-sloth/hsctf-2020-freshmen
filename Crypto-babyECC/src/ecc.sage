from secret import flag
import random

p = random_prime(2^32)
a = randint(1, 32)
b = randint(1, 32)
E = EllipticCurve(GF(p), [a, b])
g = E.random_element()

x = random_prime(2^16)
pk = x*g
k = randint(1, p-1)
kPoint = k*pk
kp = kPoint.xy()

c = []
random.seed((int(kp[0])*int(kp[1])))
for f in flag:
  c.append(ord(f)*random.getrandbits(16))

print(p)
print(a)
print(b)
print(g)
#print(g.order())
print(c)
