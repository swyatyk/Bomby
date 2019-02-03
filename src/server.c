//
// Created by Sviatoslav Prylutsky on 2/3/19.
//

#include "../headers/server.h"
char connectedClients[2][16];
int allowedClientsCount = 2;

struct {
    char name[16];
    int level , posX, posY;
} player;

int allowClientAction(char name[16]);
int isClientRegistred(char *name);

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


    while(1)
    {
        memset(buf,'\0', 128);
        if(recvfrom(server_socket,&player, sizeof(player),0,(struct sockaddr *) &client_addr, &client_adress_size)<0){
            perror("recvfrom()");
        }
        else{

            if(allowClientAction(player.name) == 0){
                printf("dont allow to connect %s", player.name);
                return;
            }


            printf("\n Received message %s from domain %s port %d internet\
 address %s\n",
                   &client_addr,
                   (client_addr.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
                   ntohs(client_addr.sin_port),
                   inet_ntoa(client_addr.sin_addr));
            printf("\n Received player info name = %s , PosX =  %d , PosY = %d \n",player.name , player.posX , player.posY);
        }
        memset(buf,'\0', 128);
    }
}

int allowClientAction(char *name) {

    int length = sizeof(connectedClients)/sizeof(int);
    if(isClientRegistred(*name)==1){
        return 1;
    }

    if(length < allowedClientsCount){
        *connectedClients[length+1] = *name;
        printf("\n");
    } else{
        return 0;
    }

}


int isClientRegistred(char *name){
    int length = sizeof(connectedClients)/sizeof(int);
    for(int i=0; i<length; i++)
    {
        if(strcmp(name , connectedClients[i]) == 0)
        {
            printf("%s  exist", connectedClients[i]);
            return 1;
        }

    }
    return 0;
}