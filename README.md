# Skyline-System简介
此操作系统是根据我以前写的PxttpOS的分支版本, 是一个用C语言写出来的操作系统,

实现的功能：

> + 1.网络
> + 2.命令行
> + 3.ls
> + 4.cat
> + 5.echo
> + 6.C语言标准库(plibc库)
> + 7.文件操作

目前的版本：
    Skyline-System V0.78c


# 如何编译？

> 运行DOC文件夹/配置环境中的envconf.sh文件(qemu配置好像有问题，请自行下载)到SRC/osmain文件夹里,运行命令:

```sh
make clean && make #清理并制作
```

> OR:

```sh
make clean && make qemu #清理并运行
```