double __cdecl func0(int *nums, int n)
{
  int i; // [rsp+Ch] [rbp-14h]
  int n1; // [rsp+10h] [rbp-10h]

  n1 = 0;
  for ( i = 0; i < n; ++i )
  {
    if ( !nums[i] )
      ++n1;
  }
  return round(100.0 * ((double)n1 / (double)n)) / 100.0;
}