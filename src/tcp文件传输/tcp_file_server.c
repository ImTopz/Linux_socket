#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>


#define SERVER_PORT 12344
#define BUFF_LEN 512

char filename[100];
char buff[1024];
char buff_end[1] = "\0";

int InitTCP()
{
    int server_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(server_fd < 0)
    {
        printf("建立tcp套接字失败！");
        return -1;
    }
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("bind error!");
        return -2;
    }
    if(listen(server_fd,SOMAXCONN)<0)
    {
        printf("listen error!");
        return -3;
    }
    return server_fd;

}

int InitAccp(int fd){
    struct sockaddr_in client_addr;
    memset(&client_addr,0,sizeof(client_addr));
    socklen_t client_len = sizeof(client_addr);
    int conn = 0;
    if((conn = accept(fd,(struct sockaddr*)&client_addr,&client_len))<0)
    {
        printf("accept error!\n");
        return -3;
    }
    printf("connect success!\n");
        
    while(1){
    recv(conn,filename,sizeof(filename),0);
    FILE *fp = fopen(filename,"w");
    if(fp == NULL)
    {
    	printf("not exits!");
        return -1;
    }
    printf("开始传送！\n");
    int temp_buffer = 0;
        while((temp_buffer = recv(conn,buff,sizeof(buff),0))>0 ){
            int cnt = 0;
            for(int i =0;i<1023;i++)
            {
                if(buff[i] == '\r' && buff[i+1] == '\n')
                {
                    cnt = 1;
                    
                }
                
            }
            
            if(cnt == 1)
            {
                fwrite('\0', sizeof(char), temp_buffer, fp);
                break;
            }

            fwrite(buff, sizeof(char), temp_buffer, fp);

          
        }
    printf("传送完毕！\n");
    fclose(fp);
    }
    close(conn);
    close(fd);
        
   
}

int main(int argc,char *argv[])
{
  
   printf("welcome to tcp file transform!\n");
   printf("开始创建套接字并进行监听！\n");
   int sock_fd = InitTCP();
   printf("starting AC!\n");
   InitAccp(sock_fd);
   

   


}
