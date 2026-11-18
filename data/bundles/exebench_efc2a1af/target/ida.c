void __cdecl rgb_2_hls(int r, int g, int b, int *h, int *l, int *s)
{
  int v6; // ecx
  int v7; // eax
  int v8; // [rsp+0h] [rbp-3Ch]
  int v9; // [rsp+4h] [rbp-38h]
  int t; // [rsp+8h] [rbp-34h]
  int max; // [rsp+Ch] [rbp-30h]
  int min; // [rsp+10h] [rbp-2Ch]

  if ( g >= r )
    v9 = r;
  else
    v9 = g;
  min = v9;
  if ( v9 > b )
    min = b;
  if ( g <= r )
    v8 = r;
  else
    v8 = g;
  max = v8;
  if ( v8 < b )
    max = b;
  *l = (max + min) / 20;
  if ( min == max )
  {
    *h = 0;
    *s = 0;
  }
  else
  {
    if ( *l >= 50 )
      v6 = 100 * (max - min) / (2000 - max - min);
    else
      v6 = 100 * (max - min) / (min + max);
    *s = v6;
    if ( r == max )
    {
      t = 60 * (g - b) / (max - min) + 120;
    }
    else
    {
      if ( g == max )
        v7 = 60 * (b - r) / (max - min) + 240;
      else
        v7 = 60 * (r - g) / (max - min) + 360;
      t = v7;
    }
    *h = t % 360;
  }
}