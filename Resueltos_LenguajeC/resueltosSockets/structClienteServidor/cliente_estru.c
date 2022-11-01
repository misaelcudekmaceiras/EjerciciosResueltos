#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<stdlib.h>
#include <unistd.h>
#include <stdio_ext.h>
#define tam 50

struct persona {
char nombre [30];
int edad;
};

union vinculo
{
    char buffer[sizeof(struct persona)];
    struct persona  dato;
};


int main(int argc , char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;

    union vinculo convertir;

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

    printf("Cargar Nombre: ");
    __fpurge(stdin);
    scanf("%s",convertir.dato.nombre);
    printf("\nCargar edad: ");
    __fpurge(stdin);
    scanf("%d",&(convertir.dato.edad));
    printf("\n");

    write(socket_desc , convertir.buffer , sizeof(struct persona));

    comuN--;
}
    close(socket_desc);


    return 0;
}
