#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include <stdio_ext.h>
#include <stdlib.h>
#define tam 50

int main(int argc , char *argv[])
{
    int socket_desc , new_socket , c;
    struct sockaddr_in server , client;
    char messageTX[tam];
    char messageRX[tam];
    int comuN=5;
    int byterx=0;
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("No se puedo crear el socket");
    }
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     

    //Ojo esto arranca el puerto
    int yes=1;
    if (setsockopt(socket_desc,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1)
    {
    perror("setsockopt");
    exit(1);
    }



    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind fallo");
        return 1;
    }
    puts("bind OK");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Espero a que un cliente se me conecte en el accept");
    c = sizeof(struct sockaddr_in);
    new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (new_socket<0)
    {
        perror("accept failed");
        return 1;
    }
     


    puts("Cliente conectado");
    printf("IP cliente: %s\t Puerto cliente: %d\n",inet_ntoa(client.sin_addr),client.sin_port);
     
while(comuN)
{
   printf("servidor dice:");
   __fpurge(stdin);
   fgets(messageTX,tam-1,stdin); //para que tome los espacios y no corte en el primero
   //printf("%s",messageTX);

    write(new_socket , messageTX , strlen(messageTX));

    if(!strcmp(messageTX,"chau\n"))
    {
    comuN=1;
    printf("chau trasmitido\n");
    }
    else
    {
    byterx=recv(new_socket, messageRX , tam-1 , 0);
    *(messageRX+byterx)='\0';// ¿preguntar estudiantes pq puse esta linea~?
    printf("cliente dice: %s\n",messageRX);
    if(!strcmp(messageRX,"chau\n"))
    {
    comuN=1;
    printf("chau recibido\n");
    }
    //strcpy(messageRX,"      ");´

    }

    //read(new_socket , messageRX , strlen(messageRX));
    comuN--;
}


    close(new_socket);
    close(socket_desc);


    return 0;
}
