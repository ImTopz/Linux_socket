#include <stdio.h>
#include "../inc/server.h"


int main()
{
    printf("starting Init TCP!\n");
    int fd = passiveTCP();
    if(fd < 0)
    {       
        printf("create TCP failed!\n");

        return -1;
    }
    printf("create socket success!\n");
    


}