//
// Created by zz on 2021/3/15.
//

#include "../unpv13e/lib/unp.h"
#include <time.h>

int main(int argc, char *argv[]) {
    // listenfd: socket fd
    // connfd: 已连接描述符，在 accept 到一个连接并成功返回（tcp 三次握手后）时得到值
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    // Socket() 是一个包装函数，内部调用了 socket()
    // socket() 创建一个 AF_INET（IPV4）SOCK_STREAM（字节流）套接字 （等同于 TCP 套接字）
    listenfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    // 绑定端口和其他信息到 socket fd
    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    // Listen() 将 套接字 转换为 监听套接字
    // LISTENQ: 允许的最大连接数，定义在 unp.h，为 1024
    Listen(listenfd, LISTENQ);

    // 死循环，不断接受来自客户端的连接请求
    for (;;) {
        // Accept() 接收客户端的连接，连接成功返回 connfd，
        // connfd 用于二者通信，并且会为每个客户创建一个 connfd
        connfd = Accept(listenfd, (SA *) NULL, NULL);

        ticks = time(NULL);
        // 美化 Unix 时间戳
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        // 向连接中写入数据
        Write(connfd, buff, strlen(buff));
        // 关闭 tcp 连接
        Close(connfd);
    }
}
