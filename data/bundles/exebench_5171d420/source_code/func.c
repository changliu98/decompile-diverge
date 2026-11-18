#include <stdint.h>

static inline int
_inverse_rot(const int *m, int *o) {
 if (m[1] == 0 || m[2] == 0)
  return 1;
 o[0] = 0;
 o[1] = (1024 * 1024) / m[2];
 o[2] = (1024 * 1024) / m[1];
 o[3] = 0;
 o[4] = - (m[5] * o[2]) / 1024;
 o[5] = - (m[4] * o[1]) / 1024;
 return 0;
}
