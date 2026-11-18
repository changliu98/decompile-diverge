int __cdecl INDMAXVAL(float *val, int i1, int i2)
{
  int ini; // [rsp+0h] [rbp-18h]
  int i; // [rsp+4h] [rbp-14h]

  ini = i1;
  for ( i = i1 + 1; i <= i2; ++i )
  {
    if ( val[i] > val[ini] )
      ini = i;
  }
  return ini;
}