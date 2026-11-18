void Sqrt(float x, float *y) {
  int i = 0x5f3759df - (x >> 1);
  float x2 = i;
  x2 = x2 * (1.5f - (x2 * x2 * x));
  if (x2 > 0)
    *y = 1 / x2;
  else
    *y = 0;
}