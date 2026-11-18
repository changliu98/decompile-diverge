void __cdecl func0(int *nums, int size)
{
  int i_4; // [rsp+Ch] [rbp-44h]
  int index_0; // [rsp+10h] [rbp-40h]
  int i_3; // [rsp+14h] [rbp-3Ch]
  int i_2; // [rsp+18h] [rbp-38h]
  int index; // [rsp+1Ch] [rbp-34h]
  int i_1; // [rsp+20h] [rbp-30h]
  int i_0; // [rsp+24h] [rbp-2Ch]
  int *count; // [rsp+28h] [rbp-28h]
  int *output; // [rsp+30h] [rbp-20h]
  int i; // [rsp+38h] [rbp-18h]
  int max_digit; // [rsp+3Ch] [rbp-14h]
  int placement; // [rsp+40h] [rbp-10h]

  placement = 1;
  max_digit = *nums;
  for ( i = 1; i < size; ++i )
  {
    if ( nums[i] > max_digit )
      max_digit = nums[i];
  }
  output = (int *)malloc(4LL * size);
  count = (int *)malloc(0x28uLL);
  while ( placement <= max_digit )
  {
    for ( i_0 = 0; i_0 < 10; ++i_0 )
      count[i_0] = 0;
    for ( i_1 = 0; i_1 < size; ++i_1 )
    {
      index = nums[i_1] / placement % 10;
      ++count[index];
    }
    for ( i_2 = 1; i_2 < 10; ++i_2 )
      count[i_2] += count[i_2 - 1];
    for ( i_3 = size - 1; i_3 >= 0; --i_3 )
    {
      index_0 = nums[i_3] / placement % 10;
      output[--count[index_0]] = nums[i_3];
    }
    for ( i_4 = 0; i_4 < size; ++i_4 )
      nums[i_4] = output[i_4];
    placement *= 10;
  }
  free(output);
  free(count);
}