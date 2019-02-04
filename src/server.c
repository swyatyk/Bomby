//
// Created by Sviatoslav Prylutsky on 2/3/19.
//

#include "../headers/server.h"
struct sockaddr_in connectedClients[2];
int allowedClientsCount = 2 , clientCnt;

struct {
    char name[16];
    int level , posX, posY;
} player;

int allowClientAction(struct sockaddr_in client);
int isClientRegistred(struct sockaddr_in client);
int GAME_RUN = 1;

void startServer() {

    printf("Server Started \n");
    int server_socket, client_adress_size;
    struct sockaddr_in client_addr, server_addr;
    int port = 1234;
    char buf[128];

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(server_socket<0){
        perror("socket()");
        exit(1);
    }
    listen(server_socket , 2);

    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if(bind(server_socket, (struct sockaddr *) &server_addr , sizeof(server_addr))<0){
      perror("bind()");
      exit(1);
    }



    printf("Whaiting for client \n");
    client_adress_size = sizeof(client_addr);

    memset(buf,'\0', 128);
    while(GAME_RUN)
    {

        if(recvfrom(server_socket,&player, sizeof(player),0,(struct sockaddr *) &client_addr, &client_adress_size)<0){
            perror("recvfrom()");
        }
        else{
            if(allowClientAction(client_addr) == 1){



                printf("\n Received client from domain %s port %d internet\
     address %s\n",

                       (client_addr.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
                       ntohs(client_addr.sin_port),
                       inet_ntoa(client_addr.sin_addr));
                printf("\n Received player info name = %s , PosX =  %d , PosY = %d \n",player.name , player.posX , player.posY);
            }
        }
        memset(buf,'\0', 128);
    }
}

int allowClientAction(struct sockaddr_in client) {

    if(isClientRegistred(client) == 1){
        printf("isClientRegistred 1 \n");
        return 1;
    }
    printf("clientCnt =  %d \n", clientCnt);
    if(clientCnt < allowedClientsCount){

        connectedClients[clientCnt] = client;
        clientCnt++;
        printf("registred new client \n");
    } else{
        printf("don't allow new clients \n");
        return 0;
    }

}


int isClientRegistred(struct sockaddr_in client){
    for(int i=0; i<clientCnt; i++)
    {

        if(connectedClients[i].sin_addr.s_addr == client.sin_addr.s_addr && connectedClients[i].sin_port == client.sin_port)
        {
            printf("already  exist \n");
            return 1;
        }

    }
    return 0;
}