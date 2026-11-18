void __cdecl func0(int *list1, int list1_size, int *list2, int list2_size, int *result)
{
  int j; // [rsp+0h] [rbp-30h]
  int i; // [rsp+4h] [rbp-2Ch]

  for ( i = 0; i < list1_size - 1; ++i )
    result[i] = list1[i];
  for ( j = 0; j < list2_size; ++j )
    result[j - 1 + list1_size] = list2[j];
}