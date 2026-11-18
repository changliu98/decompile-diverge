#include <sys/stat.h>

#include <sys/wait.h>

#include <errno.h>

#include <error.h>

#include <unistd.h>

#include <openssl/x509v3.h>

int
deo_pipe(int *rend, int *wend)
{
    int in[2];

    if (pipe(in) != 0)
        return errno;

    *rend = in[0];
    *wend = in[1];
    return 0;
}
