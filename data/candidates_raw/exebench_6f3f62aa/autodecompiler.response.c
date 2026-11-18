float rand_val(long *seed)
{
  int j;
  long k;
  static int ran1_iy, ran1_iv[32];
  float temp;

  if (*seed <= 0 || !ran1_iy) {
    if (-(*seed) < 1) *seed=1;
    else *seed = -(*seed);
    for(j = 32 + 7; j >= 0; j--) {
      k = (*seed)/127773;
      *seed = 16807*(*seed - k*127773) - k*2836;
      if(*seed < 0) *seed += 2147483647;
      if(j < 32) ran1_iv[j] = *seed;
    }
    ran1_iy = ran1_iv[0];
  }
  k = (*seed)/127773;
  *seed = 16807*(*seed - k*127773) - k*2836;
  if(*seed < 0) *seed += 2147483647;
  j = ran1_iy/(1+(2147483647 -1)/32);
  ran1_iy = ran1_iv[j];
  ran1_iv[j] = *seed;
  if((temp = (1.0/2147483647)*ran1_iy) > (1.0-1.2e-7)) return (1.0-1.2e-7);
  else return temp;
}