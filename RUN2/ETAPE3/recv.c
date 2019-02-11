#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "network.h"



void initConfigs()
{
    serverConfig.allowedClientsCount = 4;
}

int connected_clients_cnt = 0;

int main(int argc , char *argv[])
{
    initConfigs();
    int port = 0;

    int server_socket, ret;
    struct sockaddr_in serverAddr;

    int new_client;
    struct sockaddr_in newAddr;

    socklen_t addr_size;

    char buffer[128];
    pid_t new_thread;

    // if (argc != 2) {
    //   printf("usage : %s [PORT]\n", argv[0]);
    //   return -1;
    // }

    // port = atoi(argv[1]);


    Client connected_clients[serverConfig.allowedClientsCount];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0){
        perror("socket()");
        exit(1);
    }

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1234);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(server_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){
        perror("bind()");
        exit(1);
    }

    if (listen(server_socket, serverConfig.allowedClientsCount) == 0){
        printf("J'attends les clients....\n");
    } else{
        perror("listen()");
    }


    while(1){
        new_client = accept(server_socket, (struct sockaddr*)&newAddr, &addr_size);
        if(new_client < 0){
            exit(1);
        }

        printf("Tentative de connection de %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

        if(connected_clients_cnt<serverConfig.allowedClientsCount)
        {
            printf("Nouvelle connection est accepteé %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
            connected_clients[connected_clients_cnt].socket = new_client;
            connected_clients[connected_clients_cnt].connected = 1;
            connected_clients[connected_clients_cnt].connectedClient = newAddr;
            connected_clients_cnt++;
            printf("%d Client conectee \n",connected_clients_cnt);

            if((new_thread = fork()) == 0)
            {
                close(server_socket);

                while(1){
                    recv(new_client, buffer, 128, 0);
                    //printf("pid new thread = %d\n",getpid());
                    printf("Client: %s\n", buffer);
                    //send(new_client, buffer, strlen(buffer), 0);
                    if(sendto(new_client, buffer, strlen(buffer),0, (struct sockaddr *) &newAddr , sizeof(newAddr))<0)
                    {
                        bzero(buffer, sizeof(buffer));
                        printf("Deconnection de %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                        break;
                    }
                   // sendto(server_socket, buffer, strlen(buffer),0, (struct sockaddr *) &serverAddr , sizeof(serverAddr));
                    bzero(buffer, sizeof(buffer));
                }
                connected_clients_cnt--;
            }


        }
        else
            {
                printf("Connection de %s:%d est refusee! Serveur est plain \n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                close(new_client);
        }


    }

    close(new_client);


    return 0;
}


