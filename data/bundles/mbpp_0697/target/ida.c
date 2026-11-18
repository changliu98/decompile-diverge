int __cdecl func0(int *array_nums, int size)
{
  int i; // [rsp+0h] [rbp-14h]
  int count_even; // [rsp+4h] [rbp-10h]

  count_even = 0;
  for ( i = 0; i < size; ++i )
  {
    if ( !(array_nums[i] % 2) )
      ++count_even;
  }
  return count_even;
}