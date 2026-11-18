float __cdecl catmull_rom_val(int n, float *x, float xval, float *y, float *tangents)
{
  float v5; // xmm0_4
  float v6; // xmm0_4
  float v7; // xmm0_4
  float v8; // xmm0_4
  float h01; // [rsp+4h] [rbp-54h]
  float h10; // [rsp+8h] [rbp-50h]
  float h00; // [rsp+Ch] [rbp-4Ch]
  float dx_0; // [rsp+18h] [rbp-40h]
  float h; // [rsp+1Ch] [rbp-3Ch]
  int i; // [rsp+28h] [rbp-30h]
  int ival; // [rsp+2Ch] [rbp-2Ch]

  ival = n - 2;
  for ( i = 0; i < n - 2; ++i )
  {
    if ( x[i + 1] > xval )
    {
      ival = i;
      break;
    }
  }
  h = x[ival + 1] - x[ival];
  dx_0 = (float)(xval - x[ival]) / h;
  v5 = (float)(dx_0 * (float)(dx_0 * dx_0)) + (float)(dx_0 * (float)(dx_0 * dx_0)) - 3.0 * (float)(dx_0 * dx_0) + 1.0;
  h00 = v5;
  v6 = (float)(dx_0 * (float)(dx_0 * dx_0)) - 2.0 * (float)(dx_0 * dx_0) + dx_0;
  h10 = v6;
  v7 = 3.0 * (float)(dx_0 * dx_0) - ((float)(dx_0 * (float)(dx_0 * dx_0)) + (float)(dx_0 * (float)(dx_0 * dx_0)));
  h01 = v7;
  v8 = (float)(dx_0 * (float)(dx_0 * dx_0)) - 1.0 * (float)(dx_0 * dx_0);
  return (float)((float)(v8 * h) * tangents[ival + 1])
       + (float)((float)(h01 * y[ival + 1])
               + (float)((float)(h00 * y[ival]) + (float)((float)(h10 * h) * tangents[ival])));
}