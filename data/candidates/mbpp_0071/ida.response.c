void __cdecl func0(int *nums, int size)
{
  bool v2; // [rsp+1h] [rbp-21h]
  int temp; // [rsp+2h] [rbp-20h]
  int i; // [rsp+6h] [rbp-1Ch]
  int swapped; // [rsp+Ah] [rbp-18h]
  int gaps; // [rsp+Eh] [rbp-14h]

  gaps = size;
  swapped = 1;
  while ( 1 )
  {
    v2 = 1;
    if ( gaps <= 1 )
      v2 = swapped != 0;
    if ( !v2 )
      break;
    gaps = (int)(float)((float)gaps / 1.3);
    swapped = 0;
    for ( i = 0; i + gaps < size; ++i )
    {
      if ( nums[i] > nums[gaps + i] )
      {
        temp = nums[i];
        nums[i] = nums[gaps + i];
        nums[gaps + i] = temp;
        swapped = 1;
      }
    }
  }
}