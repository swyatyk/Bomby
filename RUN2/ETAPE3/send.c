/*
** ETNA PROJECT, 31/01/2019 groupe de prylut_s
** BombermanRun2
** File description:
**      etape 2 , 
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/**
 * \fn main CLIENT
 * \brief main function of our program
 *
 * \return int
 */
int main()
{
  char ip[15]= "127.0.0.1";
  int port = 1234;
  int mysocket;
  int client;
  socklen_t client_addr_len;
  struct sockaddr_in server;
  char message[128] ;

  printf("[CLIENT] choose an ip : ");
  //scanf("%s", ip); // Saisie de l'ip

  printf("[CLIENT] choose a port : ");
  //scanf("%d", &port); // Saisie du port
  printf("[CLIENT] ok \n");

  mysocket = socket(AF_INET, SOCK_STREAM, 0);
  if (mysocket < 0) {
      perror("socket()");
      return -1;
  }

  server.sin_addr.s_addr = inet_addr(ip);
  server.sin_port = htons(port);
  server.sin_family = AF_INET;

  if (connect(mysocket, (struct sockaddr *)&server, sizeof(server)) < 0) {
      perror("connect()");
      return 1;
  }

  while (1) {
    if (strcmp(message, "") == 0) {
        printf("strcmp\n ");
        memset(message, '\0', 128);
    } else {
      /* code */
      fgets(message, 128, stdin);
      if (send(mysocket, message, strlen(message), 0) < 0) {
          puts("send failed");
          close(mysocket);
          return 1;
        }
    
        printf("sended %s\n", message);
    }
    
    printf("while\n");
  }

  close(mysocket);
  return 0;
}
