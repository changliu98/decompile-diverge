void __cdecl rahms(double ra, int *h, int *m, float *s)
{
  float v4; // xmm0_4
  double temp; // [rsp+4h] [rbp-28h]
  double tempa; // [rsp+4h] [rbp-28h]
  double tempb; // [rsp+4h] [rbp-28h]

  temp = ra;
  if ( ra < 0.0 )
    temp = ra + 360.0;
  if ( temp > 360.0 )
    temp = temp - 360.0;
  tempa = temp / 15.0;
  *h = (int)tempa;
  tempb = 60.0 * (tempa - (double)(int)tempa);
  *m = (int)tempb;
  v4 = 60.0 * (tempb - (double)(int)tempb);
  *s = v4;
}