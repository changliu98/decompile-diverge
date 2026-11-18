int __cdecl func0(int *data_list, int n)
{
  int sub_length; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]
  int ia; // [rsp+Ch] [rbp-14h]
  int total; // [rsp+10h] [rbp-10h]

  total = 0;
  for ( i = 0; i < n; ++i )
  {
    if ( data_list[i] >= 0 )
    {
      total += data_list[i];
    }
    else
    {
      sub_length = -data_list[i];
      ia = i + 1;
      total += func0(&data_list[ia], sub_length);
      i = ia + sub_length - 1;
    }
  }
  return total;
}