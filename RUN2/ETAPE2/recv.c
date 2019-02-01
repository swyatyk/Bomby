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
  int client_sock;
  socklen_t client_addr_len;
  struct sockaddr_in server;
  struct sockaddr_in client_addr;
  char buff[10];


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

  listen(sock, 5);
  memset(buff, '\0', 10);

  puts("waiting clients...");
  while (1)
    {
      puts("waiting for accept");
      client_sock = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);
      if (client_sock < 0)
        {
          perror("accept()");
          return 1;
        }
      puts("new client");

      while ( (n = recv(client_sock, buff, 10, 0)) > 0 )
        {
          printf("received %s", buff);
          // write(client_sock, "ok\n", 3);
          memset(buff, '\0', 10);

          if (send(client_sock, "ok", 2, 0) < 0) {
            puts("send failed");
            close(client_sock);
            return 1;
          }
        }
    }
  close(sock);
  return 0;
}
