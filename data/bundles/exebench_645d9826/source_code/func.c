#include <errno.h>

char *byte2bin(char in, char *out) {
  int n;
  for (n = 0; n < 8; n++) out[n] = ((in & (1 << (7 - n))) == 0 ? '0' : '1');
  out[8] = '\0';
  return out;
}
