int *__cdecl func0(int n)
{
  int v1; // edx
  int i; // [rsp+4h] [rbp-1Ch]
  int *out; // [rsp+8h] [rbp-18h]

  out = (int *)malloc(4LL * (n + 1));
  *out = 1;
  if ( !n )
    return out;
  out[1] = 3;
  for ( i = 2; i <= n; ++i )
  {
    if ( i % 2 )
      v1 = (i + 1) / 2 + out[i - 2] + out[i - 1] + 1;
    else
      v1 = i / 2 + 1;
    out[i] = v1;
  }
  return out;
}