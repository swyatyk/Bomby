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
  char ip[15];
  int port;
  int mysocket;
  struct sockaddr_in server;
  char message[128] ;
  char server_reply[128];
  int firstMessage = 0;

  printf("[CLIENT] choose an ip : ");
  scanf("%s", ip); // Saisie de l'ip

  printf("[CLIENT] choose a port : ");
  scanf("%d", &port); // Saisie du port
  
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
  printf("[+] connected to server  \n");

  while (1) {
    memset(message, '\0', 128);
    fgets(message, 128, stdin);

    if (firstMessage == 0) { // Empeche l'envoi dû au scanf
        firstMessage = 1;  
    } else {
        if (send(mysocket, message, strlen(message), 0) < 0) {
            puts("[-] send failed");
            close(mysocket);
            return 1;
        }
        printf("sended %s\n", message);
        
        if (strcmp(message, "exit\n") == 0) {
            close(mysocket);
            printf("[-] disconnected");
            exit(1);
        }
        if (recv(mysocket, server_reply, 2000, 0) <= 0 )  {
            puts("server down...");
            break;
        }
        printf("server reply : %s \n", server_reply);
    }
  }

  close(mysocket);
  return 0;
}
