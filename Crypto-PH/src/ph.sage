from secret import flag
import libnum

x = libnum.s2n(flag)

ps = prime_range(2048)
pm1 = 1
p = 0
for pi in ps:
  pm1 *= pi
  if is_prime(pm1+1):
    p = pm1+1

g = randint(1, p-1)
h = pow(g, x, p)

print("p="+hex(p))
print("g="+hex(g))
print("h="+hex(h))
