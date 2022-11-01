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

    char messageTX[tam];
    char messageRX[tam];
    int comuN=5;
    int byterx=0;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Error");
    }
         
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("Error en connect");
        return 1;
    }
     
    puts("Connectado\n");
     

while(comuN)
{

    //Send some data
    if( (byterx=recv(socket_desc, messageRX , tam-1 , 0)) < 0)
    {
        puts("recv fallo");
    }
    *(messageRX+byterx)='\0';// ¿preguntar estudiantes pq puse esta linea~?
    printf("servidor dice: %s\n",messageRX);

    if(!strcmp(messageRX,"chau\n"))
    {
    printf("chau recibido\n");
    comuN=1;
    }else
    {
    printf("cliente dice:");
    __fpurge(stdin);
    fgets(messageTX,tam-1,stdin);
    write(socket_desc , messageTX , strlen(messageTX));


    if(!strcmp(messageTX,"chau\n"))
    {
    comuN=1;
    printf("chau trasmitido\n");
    }


    }

    comuN--;
}
    close(socket_desc);
    
     
    return 0;
}






