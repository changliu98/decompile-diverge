#include <math.h>

float MP_Rand(long *rand_seed)
{
  long k;
  float ans;

  *rand_seed ^= 123459876;
  k=(*rand_seed)/127773;
  *rand_seed=16807*(*rand_seed-k*127773)-2836*k;
  if (*rand_seed < 0) *rand_seed += 2147483647;
  ans=(float)((1.0/2147483647)*(*rand_seed));
  *rand_seed ^= 123459876;
  return ans;
}
