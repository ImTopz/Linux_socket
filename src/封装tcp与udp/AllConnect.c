#include "AllConnect.h"
#include "stdio.h"

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int create_socket(char* protocol, char* ip, int port) {
    int sockfd;
    struct sockaddr_in servaddr;

    // Create socket
    if(strcmp(protocol, "tcp") == 0) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
    }
    else if(strcmp(protocol, "udp") == 0) {
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    }
    else {
        printf("Invalid protocol\n");
        return -1;
    }

    // Configure server address
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if(inet_pton(AF_INET, ip, &servaddr.sin_addr) <= 0) {
        printf("Invalid IP address\n");
        return -1;
    }

    // Connect to server
    if(connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }

    return sockfd;
}


