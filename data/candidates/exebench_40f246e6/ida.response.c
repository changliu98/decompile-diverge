float __cdecl interp_tri(float *z, float x, float y, int grid_scheme)
{
  float v4; // xmm0_4
  double v7; // [rsp+0h] [rbp-88h]
  double v8; // [rsp+8h] [rbp-80h]
  double v9; // [rsp+10h] [rbp-78h]
  double v10; // [rsp+18h] [rbp-70h]
  __int128 zc; // [rsp+20h] [rbp-68h]
  double za; // [rsp+30h] [rbp-58h]
  __int128 z2; // [rsp+40h] [rbp-48h]
  double z0; // [rsp+50h] [rbp-38h]
  double yy; // [rsp+58h] [rbp-30h]
  double xx; // [rsp+60h] [rbp-28h]

  if ( x >= 0.00001 )
  {
    if ( x <= 0.99999 )
      v9 = x;
    else
      v9 = 1.0;
    v10 = v9;
  }
  else
  {
    v10 = 0.0;
  }
  xx = v10;
  if ( y >= 0.00001 )
  {
    if ( y <= 0.99999 )
      v7 = y;
    else
      v7 = 1.0;
    v8 = v7;
  }
  else
  {
    v8 = 0.0;
  }
  yy = v8;
  if ( v10 == 0.0 )
  {
    if ( v8 == 0.0 )
      return *z;
    if ( v8 == 1.0 )
      return z[2];
  }
  else if ( v10 == 1.0 )
  {
    if ( v8 == 0.0 )
      return z[1];
    if ( v8 == 1.0 )
      return z[3];
  }
  if ( grid_scheme <= 0 )
  {
    xx = 1.0 - v10;
    z0 = z[1];
    *((double *)&z2 + 1) = *z;
    *(double *)&z2 = z[2];
    v4 = z[3];
  }
  else
  {
    z0 = *z;
    *((double *)&z2 + 1) = z[1];
    *(double *)&z2 = z[3];
    v4 = z[2];
  }
  if ( xx < v8 )
  {
    za = *(double *)&z2;
    *((double *)&zc + 1) = v4;
    *(double *)&zc = z0;
    xx = 1.0 - xx;
    yy = 1.0 - v8;
  }
  else
  {
    za = z0;
    zc = z2;
  }
  return ((*(double *)&zc - za) * xx + za - ((*((double *)&zc + 1) - za) * xx + za)) * (yy / xx)
       + (*((double *)&zc + 1) - za) * xx
       + za;
}