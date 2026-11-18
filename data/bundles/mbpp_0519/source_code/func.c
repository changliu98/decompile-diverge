

#include <math.h>

#include <assert.h>



double func0(int num) {
  double volume = (pow(num, 3) / (6 * sqrt(2)));
  return round(volume * 100) / 100;
}
