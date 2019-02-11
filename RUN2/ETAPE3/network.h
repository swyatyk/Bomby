//
// Created by Sviatoslav Prylutsky on 2/6/19.
//

#ifndef BOMBERMAN_NETWORK_H
#define BOMBERMAN_NETWORK_H

 struct{
    int allowedClientsCount;
}serverConfig;

typedef struct {
    int connected;
    int socket;
    struct sockaddr_in connectedClient;
}Client;

#endif //BOMBERMAN_NETWORK_H