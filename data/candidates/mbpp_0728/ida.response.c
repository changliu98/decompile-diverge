void __cdecl func0(int *lst1, int *lst2, int *res_list, int size)
{
  int i; // [rsp+0h] [rbp-20h]

  for ( i = 0; i < size; ++i )
    res_list[i] = lst2[i] + lst1[i];
}