

#include <math.h>

#include <assert.h>



int func0(int v, int t) {
  double windchill =
      13.12 + 0.6215 * t - 11.37 * pow(v, 0.16) + 0.3965 * t * pow(v, 0.16);
  return (int)(round(windchill));
}
