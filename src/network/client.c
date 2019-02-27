/*
** ETNA PROJECT, 31/01/2019 groupe de prylut_s
** BombermanRun2
** File description:
**      etape 2 ,
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../gui/headers/gui.h"


int startClient(char* port,char *ip)
{

    int mysocket;
    struct sockaddr_in server;
    char message[128] ;
    char action[1] ;
    char server_reply[128] ;
    char mapFromServer[10][10];


    mysocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mysocket < 0) {
        perror("socket()");
        return -1;
    }


    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(atoi(port));
    server.sin_family = AF_INET;

    if (connect(mysocket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect()");
        return 1;
    }
    printf("[+] connected to server  \n");


    while (1) {
        memset(action, '\n', sizeof(action));
        action[0] = getPressedKey();
        //fgets(action, 1,action);
        if(action[0]!=10 && action[0]>0)
        {
            if (send(mysocket, action, sizeof(action), 0) < 0) {
                puts("[-] send failed\n");
                close(mysocket);
                return 1;
            }
            printf("sended %c\n", action[0]);
            if (recv(mysocket, mapFromServer, sizeof(mapFromServer), 0) <= 0 )  {
                puts("server down...\n");
                break;
            }
            printf("server reply : %s \n", server_reply);
            char *p = &mapFromServer[0][0];
            printGraphicMapFromSever(p);
        }

    }

    close(mysocket);
    return 0;
}
