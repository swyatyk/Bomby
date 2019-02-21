//
// Created by Sviatoslav Prylutsky on 2/6/19.
//

#include "bomberman.h"

#ifndef BOMBERMAN_NETWORK_H
#define BOMBERMAN_NETWORK_H

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

void initConfigs();
void initClients(Client *connected_clients);
int itsNewClient(Client *connected_clients,int new_client);
int acceptNewClient( Client *connected_clients,int new_client , struct sockaddr_in client_address , int *connected_clients_cnt);
void initListeners(Client *connected_clients,fd_set *file_discriptor , struct timeval waiting_time);
int read_client(int client);
void checkMessages(Client *connected_clients,fd_set *file_discriptor, int *connected_clients_cnt);

#endif //BOMBERMAN_NETWORK_H
