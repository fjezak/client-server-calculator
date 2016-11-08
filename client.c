#include<stdio.h> 
#include<string.h>   
#include<sys/socket.h>   
#include<arpa/inet.h> 

int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char dzialanie[1000] , wynik[2000];
    char *adress=argv[1] ;
    int port=atoi(argv[2]);


printf( "adress = %s\n", adress );
//printf("adres serwera: %s ",adress);
printf("port: %d\n",port );



    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Nie można utworzyć gniazda");
    }
    puts("Gniazd utworzone");

    server.sin_addr.s_addr = inet_addr(adress);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("Brak połączenia");
        return 1;
    }

    puts("Połączono\n");

    while(1)
    {
        printf("Wpisz działanie : liczba znak liczba : ");
        fgets( dzialanie, sizeof(dzialanie),stdin);
        puts(dzialanie);



        if( send(sock , dzialanie , strlen(dzialanie) , 0) < 0)
        {
            puts("Wysyłanie nie udane");

            return 1;
        }



        if( recv(sock , wynik , 2000 , 0) < 0)
        {
            puts("Odbieranie nie udane");
            break;
        }

        puts("WYNIK :");
        puts(wynik);
        memset(wynik,0,strlen(wynik));
    }

    close(sock);
    return 0;
}

