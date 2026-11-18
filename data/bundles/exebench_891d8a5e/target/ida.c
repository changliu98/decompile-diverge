void __cdecl decdms(double dec, int *d, int *m, float *s)
{
  float v4; // xmm0_4
  double temp; // [rsp+4h] [rbp-28h]
  double tempa; // [rsp+4h] [rbp-28h]

  *d = (int)dec;
  temp = dec - (double)(int)dec;
  if ( temp < 0.0 )
    temp = -(dec - (double)(int)dec);
  tempa = 60.0 * temp;
  *m = (int)tempa;
  v4 = 60.0 * (tempa - (double)(int)tempa);
  *s = v4;
}