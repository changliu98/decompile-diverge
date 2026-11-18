int __cdecl func0(int *array_nums, int n)
{
  int i; // [rsp+0h] [rbp-14h]
  int count_odd; // [rsp+4h] [rbp-10h]

  count_odd = 0;
  for ( i = 0; i < n; ++i )
  {
    if ( array_nums[i] % 2 )
      ++count_odd;
  }
  return count_odd;
}