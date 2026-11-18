void __cdecl standardize(int n, long *min1, long *max1, long *step1, long *min2, long *max2, long *step2)
{
  long k; // [rsp+0h] [rbp-38h]

  for ( k = 0LL; k < 3; ++k )
  {
    if ( k >= n )
    {
      min1[k] = 0LL;
      max1[k] = 1LL;
      step1[k] = 1LL;
    }
    else
    {
      min1[k] = min2[k];
      max1[k] = max2[k];
      step1[k] = step2[k];
    }
  }
}