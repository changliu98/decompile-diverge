#include <stdint.h>

static inline void
scale_mat(int *m, int sx, int sy) {
 if (sx != 1024) {
  m[0] = m[0] * sx / 1024;
  m[2] = m[2] * sx / 1024;
  m[4] = m[4] * sx / 1024;
 }
 if (sy != 1024) {
  m[1] = m[1] * sy / 1024;
  m[3] = m[3] * sy / 1024;
  m[5] = m[5] * sy / 1024;
 }
}
