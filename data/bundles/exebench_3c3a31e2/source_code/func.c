#include <pthread.h>

#include <arpa/inet.h>

#include <sys/socket.h>

#include <unistd.h>

#include <linux/if.h>

#include <sys/ioctl.h>

#include <sys/mman.h>

#include <sched.h>

int wfaCtrlRecv(int sock, unsigned char *buf)
{
    int bytesRecvd = 0;

    bytesRecvd = recv(sock, buf, 1024 -1, 0);

    return bytesRecvd;
}
