void __cdecl rgb2hsv(int r, int g, int b, int *h, int *s, int *v)
{
  int v6; // ecx
  int v7; // [rsp+0h] [rbp-38h]
  int v8; // [rsp+4h] [rbp-34h]
  int min; // [rsp+8h] [rbp-30h]
  int max; // [rsp+Ch] [rbp-2Ch]

  if ( r <= g )
    v8 = g;
  else
    v8 = r;
  max = v8;
  if ( b > v8 )
    max = b;
  if ( r >= g )
    v7 = g;
  else
    v7 = r;
  min = v7;
  if ( b < v7 )
    min = b;
  if ( max )
  {
    if ( max == min )
    {
      *h = 0;
    }
    else if ( max == r && g >= b )
    {
      *h = 600 * (g - b) / (max - min);
    }
    else if ( max == r && g < b )
    {
      *h = 10 * (60 * (g - b) / (max - min) + 360);
    }
    else
    {
      if ( max == g )
        v6 = 10 * (60 * (b - r) / (max - min) + 120);
      else
        v6 = 10 * (60 * (r - g) / (max - min) + 240);
      *h = v6;
    }
    while ( *h < 0 )
      *h += 3600;
    while ( *h >= 3600 )
      *h -= 3600;
    *s = 255 * (max - min) / max;
    *v = max;
  }
  else
  {
    *v = 0;
    *h = 0;
    *s = 0;
  }
}