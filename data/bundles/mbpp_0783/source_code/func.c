#include <math.h>

#include <stdio.h>

#include <assert.h>



void func0(int r, int g, int b, double *h, double *s, double *v) {
  double rd = r / 255.0;
  double gd = g / 255.0;
  double bd = b / 255.0;
  double mx = fmax(rd, fmax(gd, bd));
  double mn = fmin(rd, fmin(gd, bd));
  double df = mx - mn;
  *h = 0;
  if (df > 0) {
    if (mx == rd) {
      *h = fmod((60.0 * ((gd - bd) / df) + 360.0), 360.0);
    } else if (mx == gd) {
      *h = fmod((60.0 * ((bd - rd) / df) + 120.0), 360.0);
    } else if (mx == bd) {
      *h = fmod((60.0 * ((rd - gd) / df) + 240.0), 360.0);
    }
  }
  if (mx == 0) {
    *s = 0;
  } else {
    *s = (df / mx) * 100.0;
  }
  *v = mx * 100.0;
}
