#include <syscall.h>

#include <unistd.h>

#include <stddef.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <dirent.h>

#include <fcntl.h>

void strrev(char *p)
{
  char *q = p;
  while(q && *q) ++q;
  for(--q; p < q; ++p, --q)
    *p = *p ^ *q,
    *q = *p ^ *q,
    *p = *p ^ *q;
}
