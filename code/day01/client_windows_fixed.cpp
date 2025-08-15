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

    printf("Connecting to server...\n");

    // 连接服务器
    if (connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        printf("connect failed: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("Connected to server successfully!\n");

    // 关闭连接
    closesocket(sockfd);
    WSACleanup();
    
    return 0;
}
