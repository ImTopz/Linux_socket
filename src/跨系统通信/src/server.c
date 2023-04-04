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

int RecvFile(fd){
    char filename[100];
    char buffer[BUFFSIZE];
    struct sockaddr_in _addr;
    int _fd = accept(fd,(struct sockaddr*)&_addr,(socklen_t*)sizeof(_addr));
    if(_fd<0){
        printf("Error!\n");
        return -2;
        }

    while(1){
      
        printf("connect success!\n");
        recv(_fd,filename,sizeof(filename),0);
        FILE *fp = fopen(filename,"w");
        printf("start transport!\n");
        int t;
        while ((t = recv(_fd, buffer, BUFFSIZE, 0)) > 0) 
        { fwrite(buffer, sizeof(char), t, fp);}
        printf("transport finish\n");
        fclose(fp);

    }
    close(_fd);
    return 0;

}








