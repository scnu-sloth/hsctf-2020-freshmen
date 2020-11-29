不公开文件：secret.py
题文件：rsa.py output
答案：get.py

题名：Just RSA! (ver.3)
描述：看来你已经学会RSA了，随便拿点东西来加密一下吧！
hints：
1. 也许你需要gcd

flag：HSCTF{Aba_Aba_Aba_Aba_Aba}

---

令：
$$
p^e \equiv x\ (mod\ n)
$$
两边乘个q：
$$
(q*p)*p^{e-1} \equiv q*x\ (mod\ n)
$$
因为n=p\*q：
$$
q*x \equiv 0\ (mod\ n)
$$
即：
$$
q*x = k*p*q
$$
即：
$$
x = k*p
$$
然后上个gcd就求出p了：
$$
gcd(x, n) =gcd(kp, pq)=p
$$
