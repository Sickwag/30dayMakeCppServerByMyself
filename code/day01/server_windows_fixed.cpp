#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    // 初始化Windows Socket
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // 创建socket
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("socket failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // 设置服务器地址
    struct sockaddr_in serv_addr;
    memset\(&serv_addr, 0,, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);

    // 绑定socket
    if (bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        printf("bind failed: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // 监听连接
    if (listen(sockfd, SOMAXCONN) == SOCKET_ERROR) {
        printf("listen failed: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("Server listening on 127.0.0.1:8888...\n");

    // 接受客户端连接
    struct sockaddr_in clnt_addr;
    int clnt_addr_len = sizeof(clnt_addr);
    memset\(&clnt_addr, 0,, sizeof(clnt_addr));

    SOCKET clnt_sockfd = accept(sockfd, (sockaddr*)&clnt_addr, &clnt_addr_len);
    if (clnt_sockfd == INVALID_SOCKET) {
        printf("accept failed: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("New client connected! Socket: %lld, IP: %s, Port: %d\n", 
           clnt_sockfd, inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));

    // 关闭连接
    closesocket(clnt_sockfd);
    closesocket(sockfd);
    WSACleanup();
    
    return 0;
}
