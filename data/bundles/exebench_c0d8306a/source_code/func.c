#include <string.h>

#include <stdlib.h>

#include <pwd.h>         /* needed in file_openfile */

#include <sys/types.h>

#include <sys/stat.h>

#include <unistd.h>      /* contains prototype of UNIX file truncate fn  */

int file_getversion(int *version)
{
    *version = 10;
    return(0);
}
