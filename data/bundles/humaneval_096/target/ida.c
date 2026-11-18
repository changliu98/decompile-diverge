int *__cdecl func0(int n, int *count)
{
  int k; // [rsp+8h] [rbp-28h]
  int isp; // [rsp+Ch] [rbp-24h]
  int j; // [rsp+10h] [rbp-20h]
  int i; // [rsp+14h] [rbp-1Ch]
  int *out; // [rsp+18h] [rbp-18h]

  out = (int *)malloc(4LL * n);
  *count = 0;
  for ( i = 2; i < n; ++i )
  {
    isp = 1;
    for ( j = 0; j < *count; ++j )
    {
      k = out[j];
      if ( k * k > i )
        break;
      if ( !(i % k) )
      {
        isp = 0;
        break;
      }
    }
    if ( isp )
      out[(*count)++] = i;
  }
  return out;
}