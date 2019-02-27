//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../gui/headers/gui.h"


int sendPacketToServer(int mysocket)
{
    char action[1];
    memset(action, '\n', sizeof(action));
    action[0] = getPressedKey();
    if(action[0]!=10) {
        if (send(mysocket, action, sizeof(action), 0) < 0) {
            puts("[-] send failed\n");
            close(mysocket);
            return -1;
        }
        printf("sended %c\n", action[0]);
        return 1;
    }
    return 0;
}

int readServerPacket(int mysocket)
{
    char mapFromServer[10][10];
    if (recv(mysocket, mapFromServer, sizeof(mapFromServer), 0) <= 0 )  {
        puts("server down...\n");
        return -1;
    }
    printf("server reply \n");
    char *p = &mapFromServer[0][0];
    printGraphicMapFromSever(p);
    return 0;
}

int startClient(char* port,char *ip)
{
    int mysocket;
    struct sockaddr_in server;


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
    readServerPacket(mysocket);

    while (1)
    {
        if(sendPacketToServer(mysocket)==1)
        {
            if(readServerPacket(mysocket) < 0){
                printf("connection lost \n");
                break;
            }
        }
    }

    close(mysocket);
    return 0;
}
