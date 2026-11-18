#include <stddef.h>

#include <stdlib.h>

#include <string.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <limits.h>

#include <unistd.h>

#include <fcntl.h>

#include <dirent.h>

#include <stdio.h>

#include <errno.h>

void ddelete_c(char *path,int *iostat)



{
  *iostat = ( unlink(path) ? errno : 0 );
}
