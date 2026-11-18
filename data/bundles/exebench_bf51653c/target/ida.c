void __cdecl upzero(int dlt, int *dlti, int *bli)
{
  int wd2; // [rsp+4h] [rbp-20h]
  int i; // [rsp+8h] [rbp-1Ch]
  int ia; // [rsp+8h] [rbp-1Ch]

  if ( dlt )
  {
    for ( ia = 0; ia < 6; ++ia )
    {
      if ( dlti[ia] * (__int64)dlt < 0 )
        wd2 = -128;
      else
        wd2 = 128;
      bli[ia] = ((255LL * bli[ia]) >> 8) + wd2;
    }
  }
  else
  {
    for ( i = 0; i < 6; ++i )
      bli[i] = (255LL * bli[i]) >> 8;
  }
  dlti[5] = dlti[4];
  dlti[4] = dlti[3];
  dlti[3] = dlti[2];
  dlti[1] = *dlti;
  *dlti = dlt;
}