//
// Created by Sviatoslav Prylutsky on 2/6/19.
//

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

#endif //BOMBERMAN_NETWORK_H
