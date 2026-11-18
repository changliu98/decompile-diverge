int __cdecl mean3(int a, int b, int c, int white, int *err)
{
  int v7; // [rsp+4h] [rbp-64h]
  int v8; // [rsp+8h] [rbp-60h]
  int v9; // [rsp+Ch] [rbp-5Ch]
  int v10; // [rsp+10h] [rbp-58h]
  int v11; // [rsp+14h] [rbp-54h]
  int v12; // [rsp+18h] [rbp-50h]
  int v13; // [rsp+20h] [rbp-48h]
  int v14; // [rsp+24h] [rbp-44h]
  int v15; // [rsp+2Ch] [rbp-3Ch]
  int v16; // [rsp+30h] [rbp-38h]
  int v17; // [rsp+34h] [rbp-34h]
  int v18; // [rsp+38h] [rbp-30h]
  int v19; // [rsp+40h] [rbp-28h]
  int m; // [rsp+44h] [rbp-24h]

  m = (c + b + a) / 3;
  if ( err )
  {
    if ( a - m <= 0 )
      v19 = m - a;
    else
      v19 = a - m;
    if ( b - m <= 0 )
      v18 = m - b;
    else
      v18 = b - m;
    if ( v19 <= v18 )
    {
      if ( b - m <= 0 )
        v15 = m - b;
      else
        v15 = b - m;
      v16 = v15;
    }
    else
    {
      if ( a - m <= 0 )
        v17 = m - a;
      else
        v17 = a - m;
      v16 = v17;
    }
    if ( c - m <= 0 )
      v14 = m - c;
    else
      v14 = c - m;
    if ( v16 <= v14 )
    {
      if ( c - m <= 0 )
        v7 = m - c;
      else
        v7 = c - m;
      v8 = v7;
    }
    else
    {
      if ( a - m <= 0 )
        v13 = m - a;
      else
        v13 = a - m;
      if ( b - m <= 0 )
        v12 = m - b;
      else
        v12 = b - m;
      if ( v13 <= v12 )
      {
        if ( b - m <= 0 )
          v9 = m - b;
        else
          v9 = b - m;
        v10 = v9;
      }
      else
      {
        if ( a - m <= 0 )
          v11 = m - a;
        else
          v11 = a - m;
        v10 = v11;
      }
      v8 = v10;
    }
    *err = v8;
  }
  if ( a < white && b < white && c < white )
    return (c + b + a) / 3;
  if ( m <= white )
    return white;
  else
    return (c + b + a) / 3;
}