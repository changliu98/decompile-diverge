#include <stdio.h>

#include <stdlib.h>

#include <stdint.h>

#include <string.h>

#include <ctype.h>

#include <pthread.h>

#include <unistd.h>

#include <errno.h>

#include <sys/socket.h>

#include <sys/epoll.h>

#include <arpa/inet.h>

static void clean_fd(int sock, int *cache_sock, int *nsock) {
    int i;
    for (i = 0; i < 2; i++) {
        if (cache_sock[i] == sock)
            cache_sock[i] = 0;
    }

    close(sock);
    (*nsock)--;
}
