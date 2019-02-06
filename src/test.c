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

#define ARRSIZE(x)  (sizeof(x) / sizeof((x)[0]))

typedef struct {
    int b;
}Alfa;

typedef struct {
    int b;
    char *c;
}beta;



void add(beta **arr,int i)
{
    beta *b = (beta*)malloc(sizeof(beta));
    b->b=5;
    b->c="hello";
    arr[i] = b;
}

int main(){

    beta **betas = (beta **)malloc(sizeof(beta));
    add(betas,0);
    add(betas,1);
    add(betas,2);
    add(betas,3);

    betas[0]->b=10;
    betas[0]->c= "welcome";

    printf("b1c = %s , b1i = %d \n",betas[0]->c,betas[0]->b);
    printf("b2c = %s , b2i = %d \n",betas[1]->c,betas[1]->b);
    printf("size = %ld \n",  sizeof(**betas)/ sizeof(*betas[0]));


    return 1;
}



