#include <stddef.h>

void check_long(long *x,long *y,char* ret) {
  *ret = ((char*)y)-((char*)x) == sizeof(*x) ? 't' : 'f';
}
