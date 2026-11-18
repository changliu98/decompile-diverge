#include <stdbool.h>

#include <stdio.h>

#include <unistd.h>

#include <sys/syscall.h>

#include <sys/time.h>

#include <time.h>

#include <malloc.h>

#include <pthread.h>

#include <stdlib.h>

#include <string.h>

void bo_backoff(int *bwait, int cap) {
  for(int i = *bwait; i; i--);
  *bwait = (((*bwait*2) < (cap)) ? (*bwait*2) : (cap));
}
