void __cdecl func0(int *input_list, int list_size, int n, int *output_list, int *output_size)
{
  int v5; // ecx
  int i; // [rsp+0h] [rbp-28h]
  int j; // [rsp+4h] [rbp-24h]

  j = 0;
  for ( i = 0; i < list_size; i += n )
  {
    v5 = j++;
    output_list[v5] = input_list[i];
  }
  *output_size = j;
}