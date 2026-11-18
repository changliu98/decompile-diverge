int *__cdecl func0(int n)
{
  int i; // [rsp+4h] [rbp-1Ch]
  int prod; // [rsp+8h] [rbp-18h]
  int sum; // [rsp+Ch] [rbp-14h]
  int *out; // [rsp+10h] [rbp-10h]

  out = (int *)malloc(4LL * n);
  sum = 0;
  prod = 1;
  for ( i = 1; i <= n; ++i )
  {
    sum += i;
    prod *= i;
    if ( i % 2 )
      out[i - 1] = sum;
    else
      out[i - 1] = prod;
  }
  return out;
}