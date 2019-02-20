/*
** ETNA PROJECT, 31/01/2019 groupe de prylut_s
** BombermanRun2
** File description:
**      etape 2 , 
*/

#include "bomberman.h"

/**
 * \fn main CLIENT
 * \brief main function of our program
 *
 * 
 */

void playerConnect(bomber* game, char *ip, char* port)
{
  int portServer = 0;
  game->sock = 0;
  //struct sockaddr_in server;

  portServer = atoi(port);
  
   game->sock = socket(AF_INET, SOCK_STREAM, 0);
  if (game->sock < 0) {
      perror("socket()");
      exit(1);
  }
  

  game->server.sin_addr.s_addr = inet_addr(ip);
  game->server.sin_port = htons(portServer);
  game->server.sin_family = AF_INET;

  if (connect( game->sock, (struct sockaddr *)&game->server, sizeof(game->server)) < 0) {
      perror("connect()");
      exit(1);
  }
  printf("[+] connected to server  \n");
    //game->start = 1;
 /* while (1) {
    memset(message, '\0', 128);
    fgets(message, 128, stdin);
    if (send(mysocket, message, strlen(message), 0) < 0) {
        puts("[-] send failed\n");
        close(mysocket);
        exit(1);
    }
    printf("sended %s\n", message);
    
    if (strcmp(message, "exit\n") == 0) {
        close(mysocket);
        printf("[-] disconnected\n");
        exit(1);
    }
    if (recv(mysocket, server_reply, 2000, 0) <= 0 )  {
        puts("server down...\n");
        exit(1);
    }
    printf("server reply : %s \n", server_reply);
    if (strcmp(server_reply, "[!] full server") == 0) {
        printf("[-] disconnected\n");
        exit(1);
    }
  }

  close(mysocket);*/
}

int sendMess(bomber* game, char* message)
{
    //char server_reply[128];
    //memset(message, '\0', 128);
    if (send(game->sock, message, strlen(message), 0) < 0) {
        puts("[-] send failed\n");
        close(game->sock);
        exit(1);
    }
    return (1);
}