#include <iostream>
#include<windows.h>
#include<winsock2.h>
#include <string.h>
#include <unistd.h>
#include "util.h"
#pragma comment(lib, "ws2_32.lib")


int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    errif(sockfd == -1, "socket create error");

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);

    errif(connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1, "socket connect error");
    
    while(true){
        char buf[1024];
        memset(&buf, 0, sizeof(buf));
        scanf("%s", buf);
        ssize_t write_bytes = write(sockfd, buf, sizeof(buf));
        if(write_bytes == -1){
            printf("socket already disconnected, can't write any more!\n");
            break;
        }
        memset(&buf, 0, sizeof(buf));
        ssize_t read_bytes = read(sockfd, buf, sizeof(buf));
        if(read_bytes > 0){
            printf("message from server: %s\n", buf);
        }else if(read_bytes == 0){
            printf("server socket disconnected!\n");
            break;
        }else if(read_bytes == -1){
            close(sockfd);
            errif(true, "socket read error");
        }
    }
    close(sockfd);
    return 0;
}
