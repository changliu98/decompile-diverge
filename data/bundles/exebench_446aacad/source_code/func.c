#include <assert.h>

#include <stdio.h>

#include <stdlib.h>

#include <sys/types.h>

#include <sys/ipc.h>

#include <sys/sem.h>

int cond_read_lock( int *lk )
{
   int result;
   ;;
   if (*lk>=0) {
      *lk = *lk + 1;
      result = 1;
   }
   else {
      result = 0;
   }
   ;;
   return result;
}
