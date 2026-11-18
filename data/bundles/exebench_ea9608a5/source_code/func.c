#include <errno.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

void dec2bin(int n, char *rbn) {
 while(n > 0) {
  (n & 0x1) ? (*rbn++ = '1') : (*rbn++ = '0');
  n >>= 1;
 }
}
