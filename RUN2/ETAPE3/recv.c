/*
** ETNA PROJECT, 31/01/2019 groupe de prylut_s
** BombermanRun2
** File description:
**      etape 3 , 
*/



#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/**
 * \fn main SERVER
 * \brief main function for our program
 *
 * \return int
 */
int   main()
{
  int port;
  int n;
  int sock;
  struct sockaddr_in server;

  int client_sock;
  socklen_t client_addr_len;
  struct sockaddr_in client_addr;

  char buff[16];
  pid_t childpid;


  printf("[SERVEUR] choose a port : ");
  scanf("%d", &port); // Saisie du port

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
    {
      perror("socket()");
      return 1;
    }

  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
      perror("bind()");
      return 1;
    }

  if (listen(sock, 4) == 0) {
    puts("waiting clients...");
  }

  memset(buff, '\0', 16);

  while (1)
    {
      client_sock = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);
      if (client_sock < 0) {
          // perror("accept()");
          exit(1);
        }
      printf("new client from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

      if ((childpid = fork()) == 0) {
        close(sock);

        while ( (n = recv(client_sock, buff, 16, 0)) > 0 )
          {
            printf("received %s", buff);
            if (strcmp(buff, "exit\n") == 0) {
                printf("disconnected from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                break;
            }
            memset(buff, '\0', 16);

            if (send(client_sock, "ok", 2, 0) < 0) {
              puts("send failed");
              close(client_sock);
              return 1;
            }
          }
      }
    }
    
  close(sock);
  return 0;
}
