#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "network.h"

void initConfigs()
{
    serverConfig.allowedClientsCount = 4;
}

void initClients(Client *connected_clients)
{
    for(int i = 0; i < serverConfig.allowedClientsCount;i++) {
        connected_clients[i].id = i+1;
        connected_clients[i].socket = -1;
        connected_clients[i].connected = DISCONNECTED;
    }
}

int itsNewClient(Client *connected_clients,int new_client)
{
    if(new_client < 0 ) 
        return 0;
    for(int i = 0; i < serverConfig.allowedClientsCount;i++) {
        if(connected_clients[i].socket == new_client && connected_clients[i].connected == CONNECTED)
            return  0;
    }
    return 1;
}

int acceptNewClient( Client *connected_clients,int new_client , struct sockaddr_in client_address , int *connected_clients_cnt)
{
    if(*connected_clients_cnt == serverConfig.allowedClientsCount)
        return 0;
    for(int i = 0; i < serverConfig.allowedClientsCount;i++) {
        if(connected_clients[i].socket == -1 && connected_clients[i].connected == DISCONNECTED){
            connected_clients[i].socket = new_client;
            connected_clients[i].connected = CONNECTED;
            connected_clients[i].client_address = client_address;
            *connected_clients_cnt+=1;
            return 1;
        }
    }
    return 0;

}
void initListeners(Client *connected_clients,fd_set *file_discriptor , struct timeval waiting_time)
{
    int sockSum = 0;
    for (int i = 0; i < serverConfig.allowedClientsCount; i++) {
        if (connected_clients[i].connected == CONNECTED) {
            FD_SET(connected_clients[i].socket, file_discriptor);
            sockSum += connected_clients[i].socket;
        }
    }
    select(sockSum + 1, file_discriptor, NULL, NULL, &waiting_time);
}

int read_client(int client)
{
    int  n;
    char buff[128];

    if (client == -1)
        return 1;
    n = 0;
    memset(buff, '\0', 128);
    while ( (n = recv(client, buff, 128, 0)) >= 0) {
        if (n == 0)
            return -1;
        printf("received %s", buff);
        if (buff[n - 1] == '\n') {
            memset(buff, '\0', 128);
            break;
        }
    }
    return 0;
}

void checkMessages(Client *connected_clients,fd_set *file_discriptor, int *connected_clients_cnt)
{

    for (int i = 0; i < serverConfig.allowedClientsCount; i++) {
        if (connected_clients[i].connected == CONNECTED) {
            if(FD_ISSET(connected_clients[i].socket, file_discriptor)) {
                if (read_client(connected_clients[i].socket) == -1) {
                    if(*connected_clients_cnt!=0) 
                        *connected_clients_cnt-=1;
                    printf("Player:(%d)%s:%d disconnected\n", connected_clients[i].id, inet_ntoa(connected_clients[i].client_address.sin_addr), ntohs(connected_clients[i].client_address.sin_port));
                    connected_clients[i].connected = DISCONNECTED;
                    close(connected_clients[i].socket);
                    connected_clients[i].socket = -1;
                } 
                // else
                //     write(connected_clients[i].socket, "ok\n", 2);
            }
        }
    }
}

int main(int argc, char* argv[]){
    initConfigs();
    int server_socket, ret;
    struct sockaddr_in serverAddr;  
    struct timeval waiting_time;
    int connected_client;
    struct sockaddr_in newAddr;
    socklen_t addr_size;
    fd_set file_discriptor;
    char buffer[128];
    Client connected_clients[serverConfig.allowedClientsCount];
    int connected_clients_cnt = 0;

    if (argc != 2) {
        printf("usage : %s PORT\n", argv[0]);
        return -1;
    }
    
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(server_socket, F_SETFL, O_NONBLOCK);
    if(server_socket < 0){
        perror("socket()");
        exit(1);
    }
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[1]));
    initClients(connected_clients);
    if(bind(server_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){
        perror("bind()");
        exit(1);
    }
    if(listen(server_socket, serverConfig.allowedClientsCount) == 0)
        printf("waiting clients....\n");
    else
        perror("listen()");
    while(1) {
        waiting_time.tv_sec = 1;
        waiting_time.tv_usec = 0;
        connected_client = accept(server_socket, (struct sockaddr *) &newAddr, &addr_size);
        FD_ZERO(&file_discriptor);
        if (connected_client > 0) {
            printf("Connection attempt of %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
            if(itsNewClient(connected_clients,connected_client) && acceptNewClient(connected_clients,connected_client, newAddr , &connected_clients_cnt)) {
                printf("New connection %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                printf("%d Client connected\n", connected_clients_cnt);
                if(connected_clients_cnt < serverConfig.allowedClientsCount) {
                    printf("%d Slot still available\n", serverConfig.allowedClientsCount-connected_clients_cnt);
                }
                else if(connected_clients_cnt == 4)
                    printf("no more slot available\n");
            }
            else{
                printf("Connection of %s:%d refused! Server is full\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                write(connected_client, "[!] full server\n", 15);
                close(connected_client);
            }
        }
        initListeners(connected_clients,&file_discriptor , waiting_time);
        checkMessages(connected_clients,&file_discriptor , &connected_clients_cnt);
    }
    return 0;
}


