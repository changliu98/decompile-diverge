#include <string.h>

#include <stdlib.h>

#include <pwd.h>         /* needed in file_openfile */

#include <sys/types.h>

#include <sys/stat.h>

#include <unistd.h>  /* needed for getcwd prototype on unix machines */

int stream_open(char *filename, int rwmode, int *handle)
{



    if (filename)
      rwmode = 1;

    *handle = 1;

    return(0);
}
