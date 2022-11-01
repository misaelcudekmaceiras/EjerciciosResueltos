#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<stdlib.h>
#include <unistd.h>
#include <stdio_ext.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>

#define archmax 2048


struct archivo {
char nombre [256];
unsigned long int tam;
char bytesDelArchivo[archmax];
};

union vinculo
{
    char buffer[sizeof(struct archivo)];
    struct archivo  dato;
};


int main(int argc , char *argv[])
{

    long int tama=0;//Puede ser -1 si es error
	int leido=0;
    int socket_desc;


    struct sockaddr_in server;

    union vinculo convertir;


    int byterx=0;


//abrir el archivo
//cargarlo en ram
//ver que no supere tam archmax

    //if(argc==2) checkear que este ok

	int fd = open(argv[1], O_RDONLY );
	if (fd ==-1)
	{
		// print which type of error have in a code
		printf("Error Number %d \n", errno);

		// print program detail "Success or failure"
		perror("Program");
	}else
    {
	tama=lseek(fd,0,SEEK_END);//pongo al final
    printf("El tam del archivo es %ld\n",tama);
    }


	if(tama>0 && tama <= 2048)
	{


	lseek(fd,0,SEEK_SET);//pongo al inicio
	leido=read(fd,convertir.dato.bytesDelArchivo,tama);
    convertir.dato.tam=tama;
    strcpy(convertir.dato.nombre,argv[1]);

    }else
    {
        printf("Tamaño no valido \n");
        exit(1);
    }

	if(leido==tama)
	{
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

    write(socket_desc , convertir.buffer , sizeof(struct archivo));

    close(socket_desc);

    }






    return 0;
}
