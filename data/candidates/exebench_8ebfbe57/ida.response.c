float __cdecl spline_cubic_val(int n, float *t, float tval, float *y, float *ypp)
{
  int ival; // [rsp+4h] [rbp-38h]
  int i; // [rsp+8h] [rbp-34h]
  float h; // [rsp+Ch] [rbp-30h]
  float dt; // [rsp+10h] [rbp-2Ch]

  ival = n - 2;
  for ( i = 0; i < n - 1; ++i )
  {
    if ( t[i + 1] > tval )
    {
      ival = i;
      break;
    }
  }
  dt = tval - t[ival];
  h = t[ival + 1] - t[ival];
  return dt
       * (dt * (ypp[ival] * 0.5 + dt * ((float)(ypp[ival + 1] - ypp[ival]) / (6.0 * h)))
        + -(ypp[ival + 1] / 6.0 + ypp[ival] / 3.0) * h
        + (float)((float)(y[ival + 1] - y[ival]) / h))
       + y[ival];
}