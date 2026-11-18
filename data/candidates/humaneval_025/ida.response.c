int *__cdecl func0(int n, int *size)
{
  int v2; // ecx
  int v3; // ecx
  int i; // [rsp+4h] [rbp-1Ch]
  int *out; // [rsp+8h] [rbp-18h]

  out = (int *)malloc(0x100uLL);
  *size = 0;
  for ( i = 2; i * i <= n; ++i )
  {
    while ( !(n % i) )
    {
      n /= i;
      v2 = (*size)++;
      out[v2] = i;
    }
  }
  if ( n > 1 )
  {
    v3 = (*size)++;
    out[v3] = n;
  }
  return out;
}