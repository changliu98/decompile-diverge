#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <unistd.h>

#include <time.h>

#include <pthread.h>

#include <semaphore.h>

#include <fcntl.h>

static __inline__
int fetch_and_add(int* p, int i)
{
  return __sync_fetch_and_add(p, i);
}
