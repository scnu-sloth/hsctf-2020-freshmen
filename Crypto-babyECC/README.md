不公开文件：secret.py
题文件：ecc.sage output
答案：get.sage

题名：babyECC
描述：出题人说他这题是乱出的，这可不是乱出的啊，椭圆曲线，ECC，ElGamal，连公钥都不给，训练有素，有bear来！
hints：

1. 好像有点注释忘记删了
2. 可能需要少量的爆破

flag：HSCTF{HaH4_Y0u_k0w_ecC}
改secret可动态

PS：偶尔出题防AK

---

题目中最后有个print(g.order())被注释了，打开sage构造同一个椭圆曲线后发现g的阶只有21474（是可用暴力方法遍历的范围），然后看一下加密的方法是普通的ElGamal，kPoint=k\*x\*g，然后拿kPoint的x和y的积做随机数的种子（x\*y太大不可暴力），后面就是一个一次性加密。



因为g的阶很小，所以可以把k\*x的值全遍历一遍，然后恢复kPoint，接着恢复seed，然后做一次解密。因为已知flag的开头是‘HSCTF’或‘flag’（官网有写），所以遍历出来的明文里出现‘HSCTF’或‘flag’就可以了。