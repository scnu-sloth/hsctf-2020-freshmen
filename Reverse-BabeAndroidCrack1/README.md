# BabeAndroidCrack1

## 题目本体

Type: Reverse

Description: 从BabeCrack1开始学习安卓Crack。
第一题可以使用IDA Pro的动态调试功能解题，也可以直接静态逆向分析。
选择什么方法解题都是你的自由喔～
学会用IDA Pro吧～ 哦里给

Tips1: ELF 头的 start 函数是入口，__libc_init 的第三个参数是 main 函数

Tips2: 不妨试一下在 strstr 后的判断篡改一下结果？

Tips3: 其实可以停在 strstr 的地方看到密码…… 在R0还是R1寄存器呢？

Flag: HSCTF{K7wgngW4SCx3nAWBWDtR}

## 题目编译

编译前请安装ndk，并配置环境变量。

请使用 build.sh 编译最终版本！

## 题目部署

1. 把 build/babeCrack1 发布到附件
2. 填入 题目本体 的内容即可

## 题解

这道题目是让大家熟悉 IDA Pro 的使用。把安卓破解的环境搭建起来。

最好有一台可以ROOT手机，直接就可以把 IDA Pro 的服务器放到手机里面。

如果没有可以ROOT的手机，也可以建立 ARM 指令集的虚拟机（不能是X86的）。

解决了 IDA Pro 的调试环境问题后，直接调试这个程序。

在静态分析的时候可以通过 start 函数找到真正的 main 函数位置。

通过单步调试可以慢慢找到了检测密码的位置。

该位置是一个 strstr 函数，判断用户输入的字符串是否包含了密钥。

第一种做法就是直接在 strstr 运行时提取 R1 寄存器里面对应的字符串（按 A 转为字符串）。

第二种做法是直接 strstr 运行后篡改 R0 寄存器为 非0值，让他自己输出 Flag。

第三种方法就是直接静态破解。可以看到Flag都是异或保护的，所以写个C语言的程序异或回去就好了。
