#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "../inc/server.h"



int passiveTCP()
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    bind(fd,(struct sockaddr*)&addr,sizeof(addr));
    listen(fd,LISTENQ);
    return fd;
}

int RecvFile(){
    char filename[100];
    char buff[BUFFSIZE];
    
}








