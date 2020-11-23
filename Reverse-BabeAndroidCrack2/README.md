# BabeAndroidCrack2

## 题目本体

Type: Reverse

Description: BabeCrack1是不是很简单！
来破解 BabeAndroidCrack2 吧！

Tips1: 去掉一些验证就会很顺利

Tips2: 要爆破一下某个东西

Flag: HSCTF{SuAn_n1_Niu_b@}

## 题目部署

1. 把 babeAndroidCrack2.apk 发布到附件
2. 填入 题目本体 的内容即可

## 题解

这道题是破解安卓APP的卡密的题目。

通过JEB等工具可以清楚看到下面的代码：

```java
        if (km.length() != 8) {
            Toast.makeText(getApplicationContext(), "卡密不正确", Toast.LENGTH_SHORT).show();
            return;
        }
        String pattern = "^[0-9a-f]{8}$";
        if (!Pattern.matches(pattern, km)) {
            Toast.makeText(getApplicationContext(), "卡密不正确", Toast.LENGTH_SHORT).show();
            return;
        }

        CRC32 yz = new CRC32();
        yz.update("HSTCF#".getBytes());
        yz.update(km.getBytes());
        long yzm = yz.getValue();
        if (yzm != 242294092) {
            Toast.makeText(getApplicationContext(), "卡密不正确", Toast.LENGTH_SHORT).show();
            return;
        }

        yz.reset();
        yz.update("HSTCF#".getBytes());
        yz.update(km.getBytes());
        yz.update("#".getBytes());
        yz.update(String.valueOf(yzm).getBytes());
        long yzm2 = yz.getValue();
        System.out.println(yzm2);
        if (yzm2 != 3898757979L) {
            Toast.makeText(getApplicationContext(), "卡密不正确", Toast.LENGTH_SHORT).show();
            return;
        }
```

暗示这个卡密是 8位的 十六进制字符，因此遍历的范围肯定在 `0x00000000` ~ `0xffffffff` 之间。就按照这样去爆破就完事儿～ 

注意！会有两个数字的CRC都是 `242294092`，所以还得继续用第二条公式验证，最终得到卡密 `cafebe1f`。

别以为这样就完事儿了！还得改smali重打包，把 `sendLogin` 改成无论如何都返回 `ok` 就完事儿了。

当然，有frida的话，直接HOOK这个方法，连重打包都不用哈哈哈

如果不想从Java层入手，也可以直接看Native层的代码，通过卡密构造AES的密钥来解密出Flag。
