from gmpy2 import invert
import random

p = 125102209
a = 24
b = 23
E = EllipticCurve(GF(p), [a, b])
g = E([78828931, 83986478])
order = g.order()
print(order)  # little order

gs = [g]  # G
for i in range(order-1):
  gs.append(g*(i+2))

c = [2707776, 3395364, 2543722, 1380876, 154210, 3200829, 1154664, 3677561, 4119120, 728104, 2177970, 3270750, 1017120, 1885455, 6209675, 3960926, 2937552, 5915490, 6040860, 6604794, 543906, 172056, 6854750]
for xkinv in range(1, order):
  kPoint = xkinv*g
  kp = kPoint.xy()
  random.seed((int(kp[0])*int(kp[1])))

  try:
    result = chr(c[0]//random.getrandbits(16))
  except:
    pass
  if result != 'H':
    pass

  try:
    for ci in c[1:]:
      result += chr(ci//random.getrandbits(16))
  except:
    pass

  if 'HSCTF' in result:
    print(xkinv)
    print(kp)
    print(result)
    
   


