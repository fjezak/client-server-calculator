/*
 ============================================================================
 Name        : serwer.c
 Author      : Dominik Seweryn
 Version     : 1.0.0
 Created	 : 04.11.2016
 Description : Projekt na PjC2
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write

#include "biblioteka.h"

int main(int argc , char *argv[])
{
	char buf[250];
	int port = 8883;
	if(argc == 2) {
		port = atoi(argv[1]);
		printf("Wprowadzono port %d\n", port);
		if(port == 0) port = 8883;
	}

    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( port );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");

    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
    	funkcja(client_message, buf);
    	write(client_sock , buf , strlen(buf));
    }

    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }

    if(!close(client_sock)) puts("client_sock closed");
    if(!close(socket_desc)) puts("socket_desc closed");

    return EXIT_SUCCESS;
}
