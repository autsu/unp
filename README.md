# MacOS 环境搭建

## command
```shell
cd ./unpv13e
./configure
cd lib
make
cd ../libfree
make
sudo cp ./config.h  /usr/local/include
sudo cp ./lib/unp.h  /usr/local/include

sudo cp ./libunp.a  /usr/local/lib
```

## 修改
需要修改的内容如下：（本项目中已修改）

`unpv13e/libfree/inet_ntop.c` 把 #include <arpa/inet.h> 这行注释掉

`unpv13e/lib/unp.h` 把其中的 #include "../config.h" 修改为 #include "config.h"

## 使用
`#include "unp.h"`

如果想在 ide 中查看源码，可以使用 `#include "../unpv13e/lib/unp.h"`

## 测试
可以在 NIST Internet Time Servers 来找一个可用的时间服务器地址进行测试，例如 129.6.15.28

## 编译
编译时需要指定库文件链接 -lunp    

参考：https://meik2333.com/posts/macos-unpv1-env/