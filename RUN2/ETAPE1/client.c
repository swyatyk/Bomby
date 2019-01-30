/*
** ETNA PROJECT, 31/01/2019 groupe de prylut_s
** BombermanRun2
** File description:
**      etape 1 , lancement client avec demande de saisie de l'ip et du port
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
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
  struct sockaddr_in addr;

  printf("choissisez une ip : ");
  scanf("%s", ip); // Saisie de l'ip

  printf("choissisez un port : ");
  scanf("%d", &port); // Saisie du port

  mysocket = socket(AF_INET, SOCK_STREAM, 0);
  if (mysocket < 0)
    {
      perror("socket()");
      return -1;
    }

  addr.sin_addr.s_addr = inet_addr(ip);
  addr.sin_port = htons(port);
  addr.sin_family = AF_INET;

  if (connect(mysocket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
      perror("connect()");
      return 1;
    }

  write(mysocket, "hello\n", 6);

  return 0;
}
