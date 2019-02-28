//
// Created by Sviatoslav Prylutsky on 2/6/19.
//

#ifndef BOMBERMAN_NETWORK_H
#define BOMBERMAN_NETWORK_H
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
struct{
    int allowedClientsCount;
}serverConfig;

enum NETWORK_STATUS{
    CONNECTED,
    DISCONNECTED

}network_status;

typedef struct client_s {
    int id;
    int connected;
    int socket;
    struct sockaddr_in client_address;
}Client;
int startServer();
void remapMap();
void notificateAllClients();
void setCellInServerMap(int y , int x, char ch);
#endif //BOMBERMAN_NETWORK_H