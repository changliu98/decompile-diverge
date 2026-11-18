void __cdecl mac_real(float *x, float *h, float *y)
{
  *y = (float)(*x * *h) + *y;
  y[1] = (float)(x[1] * *h) + y[1];
}