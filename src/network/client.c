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
#include <pthread.h>
#include "../gui/headers/gui.h"
static int mysocket = -1;

void * sendPacketToServer()
{
   while(1) {


        char action[1];
       memset(action, '\n', sizeof(action));
        action[0] = getPressedKey();
        if (action[0] != 10) {
            if (send(mysocket, action, sizeof(action), 0) < 0) {
                puts("[-] send failed\n");
                close(mysocket);
                break;
            }
        }
    }
    return 0;
}

void * readServerPacket()
{
    char mapFromServer[10][10];
    while (1)
    {

        if (recv(mysocket, mapFromServer, sizeof(mapFromServer), MSG_WAITALL) <= 0) {
            puts("readServerPacket server down...\n");
            break;
        }
        char *p = &mapFromServer[0][0];
        printGraphicMap(p);
        memset(mapFromServer, '\n', sizeof(mapFromServer));
    }
    return 0;
}


int startClient(char* port,char *ip)
{
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
    //readServerPacket(mysocket);

    pthread_t threadReceiver;
    if (pthread_create(&threadReceiver, NULL, readServerPacket, NULL) != 0) {
        printf("main error: can't create receiver thread \n");
    }

    pthread_t threadSender;
    if (pthread_create(&threadSender, NULL, sendPacketToServer, NULL) != 0) {
        printf("main error: can't create sender thread \n");
    }

   pthread_join(threadReceiver,NULL);
   pthread_join(threadSender,NULL);

   close(mysocket);
    return 0;
}
