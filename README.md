# Skyline-System简介
此操作系统是根据我以前写的PxttpOS的分支版本, 是一个用C语言写出来的操作系统,

实现的功能：

> + 1.网络
> + 2.命令行
> + 3.ls
> + 4.cat
> + 5.echo
> + 6.C语言标准库(plibc库)
> + 7.文件操作(包括mkdir、cd)

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

## 文档

1. [工具链搭建](SRC/osmain/notes/工具链.md)
2. [lab1 启动PC](SRC/osmain/notes/lab1.md)
3. [lab2 内存管理](SRC/osmain/notes/lab2.md)
4. [lab3A 用户环境和异常处理](SRC/osmain/notes/lab3A.md)
5. [lab3B 页面错误，断点异常和系统调用](SRC/osmain/notes/lab3B.md)
6. [lab4A 多处理器支持和协作多任务](SRC/osmain/notes/lab4A.md)
7. [lab4B/C Copy-on-Write Fork/抢占式多任务和进程间通信 (IPC)](SRC/osmain/notes/lab4BC.md)
8. [Lab 5: File system, Spawn and Shell](SRC/osmain/notes/lab5.md)
9. [Lab 6: 网络驱动程序](SRC/osmain/notes/lab6.md)
