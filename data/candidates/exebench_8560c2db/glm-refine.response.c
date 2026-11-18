unsigned int __cdecl mc_bitcode(float *val, float thres)
{
  unsigned int res = 0;

  for (unsigned int i = 0; i < 8; ++i)
  {
    if (val[i] > thres)
      res |= (1u << i);
  }
  
  return res;
}