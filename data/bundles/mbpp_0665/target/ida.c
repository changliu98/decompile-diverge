void __cdecl func0(int *num_list, int n, int *output)
{
  int v3; // ecx
  int v4; // ecx
  int i_1; // [rsp+0h] [rbp-30h]
  int i_0; // [rsp+4h] [rbp-2Ch]
  int i; // [rsp+8h] [rbp-28h]
  int output_index; // [rsp+Ch] [rbp-24h]
  int count_first; // [rsp+10h] [rbp-20h]
  int first_element; // [rsp+14h] [rbp-1Ch]

  first_element = *num_list;
  count_first = 0;
  output_index = 0;
  for ( i = 0; i < n; ++i )
  {
    if ( num_list[i] == first_element )
      ++count_first;
  }
  for ( i_0 = 0; i_0 < n; ++i_0 )
  {
    if ( num_list[i_0] != first_element )
    {
      v3 = output_index++;
      output[v3] = num_list[i_0];
    }
  }
  for ( i_1 = 0; i_1 < count_first; ++i_1 )
  {
    v4 = output_index++;
    output[v4] = first_element;
  }
}