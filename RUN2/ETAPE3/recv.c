/*
** ETNA PROJECT, 31/01/2019 groupe de prylut_s
** BombermanRun2
** File description:
**      etape 2 , 
*/



#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include "network.h"


/**
 * \fn main SERVER
 * \brief main function for our program
 *
 * \return int
 */

void registerNewClient(int client_sock, int sockets_clients[], struct sockaddr_in connectedClientsList[] ,struct sockaddr_in new_client);
int isNewClient(struct sockaddr_in connectedClientsList[] , struct sockaddr_in client);
int read_client(int client ,struct sockaddr_in client_addr);
void checkClients(int sockets_clients[],struct sockaddr_in connectedClientsList[]);

void initConfigs()
{
  serverConfig.allowedClientsCount = 4;
}

int connected_clients_cnt = 0;
fd_set readfs;
int server_socket;
socklen_t client_addr_len;


int   main()
{
  initConfigs();
  int port = 1234;
  int n;
  int client_sock;

  struct sockaddr_in server;
  struct sockaddr_in client_addr;
  struct sockaddr_in connectedClients[serverConfig.allowedClientsCount];
  int sockets_clients[serverConfig.allowedClientsCount];
  char buff[10];
  struct timeval timeout;

  printf("[SERVEUR] choose a port : ");
 // scanf("%d", &port); // Saisie du port

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket == -1)
    {
      perror("socket()");
      return 1;
    }

  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
      perror("bind()");
      return 1;
    }

  listen(server_socket, 5);
  memset(buff, '\0', 10);

  puts("waiting clients...");
  while (1)
    {
      timeout.tv_sec = 1;
      timeout.tv_usec = 0;

      FD_ZERO(&readfs);


      client_sock = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
      checkClients(sockets_clients,connectedClients);
      select(sockets_clients[connected_clients_cnt] + 1, &readfs, NULL, NULL, &timeout);
      if (client_sock < 0)
        {
          perror("accept()");
          return 1;
        }
      if(isNewClient(connectedClients,client_addr)==1)
      {
        puts("isNewClient");
        if(connected_clients_cnt<serverConfig.allowedClientsCount)
        {
          puts("connected_clients_cnt");
          registerNewClient(client_sock,sockets_clients,connectedClients,client_addr);
          puts("registerNewClient");
        }
        else
        {
          continue;
        }
      }
    }
  close(server_socket);
  return 0;
}

void checkClients(int sockets_clients[],struct sockaddr_in connectedClientsList[]){

  for(int i=0; i<connected_clients_cnt; i++)
  {
    if (FD_ISSET(sockets_clients[i], &readfs))
    {
      if (read_client(sockets_clients[i],connectedClientsList[i]) == -1)
      {
        printf("client %d disconnected \n",sockets_clients[i]);
        close(sockets_clients[i]);
        connected_clients_cnt = -1;
      }
    }
  }
}

int isNewClient(struct sockaddr_in connectedClientsList[] , struct sockaddr_in client){
    for(int i=0; i<serverConfig.allowedClientsCount; i++)
    {

        if(connectedClientsList[i].sin_port == client.sin_port && connectedClientsList[i].sin_addr.s_addr == client.sin_addr.s_addr )
        {
            printf("already exist \n");
            return 0;
        }

    }
    return 1;
}

void registerNewClient(int socket, int sockets_clients[], struct sockaddr_in connectedClientsList[] ,struct sockaddr_in new_client)
{
  FD_SET(socket, &readfs);
  connectedClientsList[connected_clients_cnt] = new_client;
  sockets_clients[connected_clients_cnt] = socket;
  connected_clients_cnt++;
  puts("registred new client \n");
}

int read_client(int client ,struct sockaddr_in client_addr)
{

  int  n;
  char buff[128];
  char message_to_client[128];

  if (client == -1)
  {
    return 1;
  }

  n = 0;
  memset(buff, '\0', 128);
  while ( (n = recv(client, buff, 128, 0)) >= 0)
  {
    if (n == 0)
    {
      return -1;
    }

    printf("received from client %s \n", buff);
    if (buff[n - 1] == '\n')
    {
      memset(buff, '\0', 128);
      break;
    }
    strcpy(message_to_client, "some message from server");
    if(sendto(server_socket,message_to_client, 128, 0,(struct sockaddr *) &client_addr,client_addr_len)<0)
    {
      perror("ERROR in sendto");
    }
  }
  return 0;
}