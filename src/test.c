//#include "../headers/bomberman.h"

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

typedef struct {
    int priority;
    char a;
}cell;

int main(){

    cell cells[6];

    cells[0].a = 'a';
    cells[1].a = 'b';
    cells[2].a = 'c';
    cells[3].a = 'd';
    cells[4].a = 'e';
    cells[5].a = 'f';

    for(int i =0 ; i < 6 ; i++)
    {
        printf("a = %c \n ", cells[i].a);
    }
    return 1;
}




