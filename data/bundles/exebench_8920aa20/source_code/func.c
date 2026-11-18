#include <pthread.h>

#include <regex.h>

int medusaReceiveInternal(int socket, unsigned char *buf, int length)
{
# 454 "medusa-net.c"
    return recv(socket, buf, length, 0);
}
