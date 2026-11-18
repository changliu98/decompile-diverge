#include <fcntl.h>

#include <sys/mman.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <unistd.h>

float mmapGet(float* addr, long i) {
 return addr[i];
}
