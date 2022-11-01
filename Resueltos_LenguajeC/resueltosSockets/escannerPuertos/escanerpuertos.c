#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<stdlib.h>
#include <unistd.h>
#include <stdio_ext.h>
#define tam 50



int main(int argc , char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;

    unsigned short int puerto=1;



if(argc>=2)
            {
                //ojo si no ponene una IP
                server.sin_addr.s_addr = inet_addr(argv[1]);
                server.sin_family = AF_INET;

            if(argc==3)
            {
                puerto=(unsigned short int)atoi(argv[2]);
            }else
            {
                puerto=1;
            }


            for(;puerto<=65535;puerto++)
            {
                socket_desc = socket(AF_INET , SOCK_STREAM , 0);
                if (socket_desc == -1)
                {
                    printf("Error");
                }
                server.sin_port = htons( puerto );

                //Connect to remote server
                if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
                {
                printf("Puerto cerrado %d\n",puerto);
                sleep(1);
                }else
                {
                printf("Connectado al puerto %d\n",puerto);
                close(socket_desc);
                sleep(1);
                }

            }

}




    return 0;
}
