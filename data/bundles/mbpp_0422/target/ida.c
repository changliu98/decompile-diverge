double __cdecl func0(int n)
{
  int i; // [rsp+Ch] [rbp-14h]
  double sum; // [rsp+10h] [rbp-10h]

  sum = 0.0;
  for ( i = 1; i <= n; ++i )
    sum = (double)(i * i * i) + sum;
  return round(sum / (double)n * 1000000.0) / 1000000.0;
}