//
// Created by Sviatoslav Prylutsky on 2/4/19.
//


#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <arpa/inet.h>

struct PLAYER {
    char name[32];
    int posX;
    int posY;

} player;

int main( int argc, char **argv)

{


    int s;
    unsigned short port;
    struct sockaddr_in server;
    char buf[128];
    memset(buf,'\0',128);


/* argv[1] is internet address of server argv[2] is port of server.
 * Convert the port from ascii to integer and then from host byte
 * order to network byte order.
 */
    if(argc != 3)
    {
        printf("Usage: %s <host address> <port> \n",argv[0]);
        exit(1);
    }
//port = htons(atoi(argv[2]));
    port = htons(1234);

    memset(player.name,'\0',32);
//strcpy(player.name,"boby");
    player.posY = 10;
    player.posX = 30;

/* Create a datagram socket in the internet domain and use the
 * default protocol (UDP).
 */
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket()");
        exit(1);
    }

/* Set up the server name */
    server.sin_family      = AF_INET;            /* Internet Domain    */
    server.sin_port        = port;               /* Server Port        */
    server.sin_addr.s_addr = inet_addr(argv[1]); /* Server's Address   */
//while(1)
    {
        /* Send the message in buf to the server */
        // memset(buf,'\0',128);
        fgets(player.name,32,stdin);

        //if (sendto(s, buf, (strlen(buf)+1), 0,(struct sockaddr *)&server, sizeof(server)) < 0)
        if (sendto(s, &player, sizeof(player), 0,(struct sockaddr *)&server, sizeof(server)) < 0)
        {
            perror("sendto()");
            exit(2);
        }
    }
/* Deallocate the socket */
    close(s);
    return 1;
}