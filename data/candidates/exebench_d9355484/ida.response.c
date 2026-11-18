void __cdecl RGBtoHSV(float r, float g, float b, float *h, float *s, float *v)
{
  float v6; // [rsp+0h] [rbp-54h]
  float v7; // [rsp+4h] [rbp-50h]
  float v8; // [rsp+8h] [rbp-4Ch]
  float v9; // [rsp+10h] [rbp-44h]
  float v10; // [rsp+14h] [rbp-40h]
  float v11; // [rsp+18h] [rbp-3Ch]
  float delta; // [rsp+20h] [rbp-34h]

  if ( b <= g )
    v11 = b;
  else
    v11 = g;
  if ( v11 <= r )
  {
    if ( b <= g )
      v9 = b;
    else
      v9 = g;
    v10 = v9;
  }
  else
  {
    v10 = r;
  }
  if ( g <= b )
    v8 = b;
  else
    v8 = g;
  if ( r <= v8 )
  {
    if ( g <= b )
      v6 = b;
    else
      v6 = g;
    v7 = v6;
  }
  else
  {
    v7 = r;
  }
  *v = v7;
  delta = v7 - v10;
  if ( v7 == 0.0 )
  {
    *s = 0.0;
    *h = -1.0;
  }
  else
  {
    *s = delta / v7;
    if ( r == v7 )
    {
      *h = (float)(g - b) / delta;
    }
    else if ( g == v7 )
    {
      *h = (float)((float)(b - r) / delta) + 2.0;
    }
    else
    {
      *h = (float)((float)(r - g) / delta) + 4.0;
    }
    *h = 60.0 * *h;
    if ( *h < 0.0 )
      *h = *h + 360.0;
  }
}