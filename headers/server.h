//
// Created by Sviatoslav Prylutsky on 2/3/19.
//

#ifndef BOMBERMAN_SERVER_H
#define BOMBERMAN_SERVER_H
#include "bomberman.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
void startServer();
#endif //BOMBERMAN_SERVER_H
