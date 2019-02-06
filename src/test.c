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
    int b;
}Alfa;

typedef struct {
    int b;
}beta;


typedef struct {
    double d;
}gamma;

 struct {
    char a;
    Alfa *alphas;
    beta *betas;
    gamma *gammas;
} cell;

 void putArr(void **arr , void *d)
 {

     printf("arr[0] = %p",arr[0]);
     arr[0] = d;
 }

int main(){

    char chars[5];
    int *ints;

    char x = 'x';
    putArr((void *)&chars,(void*) 'c');
   // putArr(ints,8);
  // chars[0]='X';

    printf("chars[0] = %c",chars[0]);
   // printf("ints[0] = %d",ints[0]);


    return 1;
}



