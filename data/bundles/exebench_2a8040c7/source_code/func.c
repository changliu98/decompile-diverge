#include <stdlib.h>

#include <string.h>

#include <sys/shm.h>

#include <sys/types.h>

long shmDetach(float *addr) {
 return shmdt(addr);
}
