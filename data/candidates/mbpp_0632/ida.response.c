void __cdecl func0(int *num_list, int size, int *result)
{
  int v3; // ecx
  int v4; // ecx
  int i_0; // [rsp+0h] [rbp-28h]
  int i; // [rsp+4h] [rbp-24h]
  int j; // [rsp+8h] [rbp-20h]
  int zero_count; // [rsp+Ch] [rbp-1Ch]

  zero_count = 0;
  j = 0;
  for ( i = 0; i < size; ++i )
  {
    if ( num_list[i] )
    {
      v3 = j++;
      result[v3] = num_list[i];
    }
    else
    {
      ++zero_count;
    }
  }
  for ( i_0 = 0; i_0 < zero_count; ++i_0 )
  {
    v4 = j++;
    result[v4] = 0;
  }
}