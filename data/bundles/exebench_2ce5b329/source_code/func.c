#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>

#include <sys/socket.h>

#include <sys/epoll.h>

void init(int* arr){
    int i = 0;
    for(i = 0; i< 10; i++)
        arr[i] = 0;

}
