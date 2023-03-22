#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define CLIENT_PORT 1234

char filename[100];
char buff[1024];
char buff2[10] = "\r\n";

int TransFile(int fd)
{
    
    while(1){
    printf("请输入文件名，长度请在100以内！\n");
    scanf("%s",filename);
    FILE *fp = fopen(filename,"r");
    if(fp == NULL)
    {
        printf("文件不存在！\n");
      
    }
    printf("开始进行传输!\n");
    
    send(fd,filename,sizeof(filename),0);
    int tmp_buff = 0;
    while( (tmp_buff = fread(buff,sizeof(char),1024,fp)) > 0 )
    {
        send(fd,buff,sizeof(buff),0);
    }
     send(fd,buff2,sizeof(buff2),0);
    
    fclose(fp);
    printf("传输完毕！\n");

    }
    return 0;

}


int InitTCP()
{   
    printf("fd initing!\n");
    int client_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    printf("%d\n",client_fd);
    if(client_fd < 0)
    {
        printf("建立套接字失败!\n");
        return -1;
    }
    printf("create success!");
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(CLIENT_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   
    int conn = connect(client_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(conn < 0)
    {
        printf("建立连接失败！\n");
        return -2;
    }

    TransFile(client_fd);

    
 
    close(conn);
    
    close(client_fd);
    return client_fd;    
}






int main(int argc,char *argv[])
{
  printf("client starting!\n");
  int client_fd = InitTCP();
  return 0;

}
