//
// Created by zz on 2021/2/28.
//

//#include "unp.h"
#include "../unpv13e/lib/unp.h"

// ./time 129.6.15.28
int main(int argc, char *argv[]) {
    // 套接字描述符
    int sockfd, n;
    char recvline[MAXLINE + 1]; // 4096 + 1
    struct sockaddr_in servaddr;

    if (argc != 2) {
        err_quit("usage: a.out <IPaddress>");
    }

    // socket() 创建一个 AF_INET（IPV4）SOCK_STREAM（字节流）套接字 （等同于 TCP 套接字）
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) ) < 0 ) {
        err_sys("socket error");
    }

    // bzero() 清空结构体
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;  // 地址族
    servaddr.sin_port = htons(13);  // 端口号

    // inet_pton() 转成大端（网络字节序列）
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        err_quit("inet_pton error for %s", argv[1]);
    }

    // connect() 创建一个套接字连接
    // 第一个参数：套接字的文件描述符
    // 第二个参数：套接字地址结构（sockaddr_in 结构体），会根据该结构的属性进行创建
    // 第三个参数：第二个参数的长度，总是使用 sizeof 获得
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr) ) < 0 ) {
        err_sys("connect error");
    }

    while ( (n = read(sockfd, recvline, MAXLINE) ) > 0 ) {
        recvline[n] = '\0';    // 添加终止符
        if (fputs(recvline, stdout) == EOF) {
            err_sys("fputs error");
        }
    }

    if (n < 0) {
        err_sys("read error");
    }

    exit(0);
}