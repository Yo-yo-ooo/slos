# Skyline-System简介
此操作系统是根据我以前写的PxttpOS的分支版本, 是一个用C语言写出来的操作系统, 可以实现一些简单的命令但是显示时间程序
(在user/time.c下)请广大网友、程序员们帮我们完善一下这个显示时间的程序.
````
实现的功能：

1.网络
2.命令行
3.ls
4.cat
5.echo
6.C语言标准库(plibc库)
7.文件操作

目前的版本：
    Skyline-System V0.7c
````

# 如何编译？

````
运行DOC文件夹中的sh文件(qemu配置好像有问题，请自行下载)
到SRC/osmain文件夹里,运行命令:

make clean && make #清理并制作

OR:

make clean && make qemu #清理并运行

````