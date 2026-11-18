unsigned int __cdecl mc_bitcode(float *val, float thres)
{
  unsigned int res; // [rsp+0h] [rbp-14h]
  unsigned int i; // [rsp+4h] [rbp-10h]

  res = 0;
  for ( i = 0; i < 8; ++i )
  {
    if ( val[i] > thres )
      res |= 1 << i;
  }
  return res;
}