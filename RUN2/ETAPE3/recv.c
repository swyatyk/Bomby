//мой рабочий вариант

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
#include <fcntl.h>

/**
 * \fn read_client
 * \brief read and print recv data from the client file descriptor until he is connected
 *
 * \param client file descriptor of the client to use
 * \return int
 */

typedef struct {
    int socket;
    struct sockaddr_in address;

}Client;
int  read_client(int client)
{
    int  n;
    char buff[128];

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

        printf("received %s", buff);

        if (buff[n - 1] == '\n')
        {
            memset(buff, '\0', 128);
            break;
        }
    }
    return 0;
}

int checkNew(int connected_cnt, Client clients[] , int sock)
{
    for(int i=0;i<connected_cnt;i++)
    {
        if(clients[i].socket == sock)
            return 0;
    }
    return 1;
}


/**
 * \fn main
 * \brief main function of our receiver
 *
 * \return int
 */
int   main()
{
    int sock;
    int client1;
    int client2;
    socklen_t client_addr_len;
    struct sockaddr_in server;
    struct sockaddr_in client_addr;

    fd_set readfs;
    struct timeval timeout;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(sock, F_SETFL, O_NONBLOCK);
    if (sock == -1)
    {
        perror("socket()");
        return 1;
    }

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind()");
        return 1;
    }

    listen(sock, 5);

    puts("waiting clients...");
    puts("waiting for accept");
    client1 = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);

    /*if (client1 < 0 || client2 < 0)
    {
        perror("accept()");
        return 1;
    }*/
    puts("new clients");

    Client clients[4];
    int connected_cnt = 0;
    int sockSum = 0;
    while (1)
    {
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        FD_ZERO(&readfs);
        clients[connected_cnt].socket = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);

        if(clients[connected_cnt].socket > 0 && checkNew(connected_cnt,clients,clients[connected_cnt].socket)==1  )
        {

            clients[connected_cnt].address = client_addr;
            puts(" new client");
            printf("connected_cnt %d \n",connected_cnt);
            printf("clients[connected_cnt].socket %d \n",clients[connected_cnt].socket);
            connected_cnt++;
        }
        for(int i=0;i<connected_cnt;i++)
        {
            FD_SET(clients[i].socket,&readfs);
            sockSum+=clients[i].socket;
        }

        select(sockSum + 1, &readfs, NULL, NULL, &timeout);

        for(int i=0;i<connected_cnt;i++)
        {

            if (FD_ISSET(clients[i].socket, &readfs))
            {
                printf("check id_isset");
                printf("client %d talks \n",clients[i].socket);
                if (read_client(clients[i].socket) == -1)
                {
                    puts("client 1 disconnected");
                    close(clients[i].socket);
                    clients[i].socket = -1;
                    connected_cnt--;
                }
            }
        }

        //clients[clients[i].socket] = -1;




        /*if (client1 == -1 && client2 == -1)
        {
            break;
        }*/

        //printf("looping");
    }
    close(sock);
    return 0;
}
