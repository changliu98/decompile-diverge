int __cdecl find_max_idx(const float *f)
{
  float v1; // xmm0_4
  int i; // [rsp+0h] [rbp-1Ch]
  int ia; // [rsp+0h] [rbp-1Ch]
  int idx; // [rsp+4h] [rbp-18h]
  float en; // [rsp+8h] [rbp-14h]

  en = 0.0;
  idx = -1;
  for ( i = 0; i < 16; ++i )
  {
    if ( f[i] > en )
    {
      en = f[i];
      idx = i;
    }
  }
  if ( idx < 0 )
    return -1;
  for ( ia = 0; ia < 16; ++ia )
  {
    if ( idx != ia )
    {
      v1 = en * 0.1;
      if ( f[ia] > v1 )
        return -1;
    }
  }
  return idx;
}