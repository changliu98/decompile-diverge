void __cdecl func0(int *list1, int list1_size, int *list2, int list2_size, int *result)
{
  int i;
  int j;

  // Copy all elements except the last one from list1 to result
  for ( i = 0; i < list1_size - 1; ++i )
    result[i] = list1[i];

  // Append all elements from list2 to result, overwriting the last element of list1
  for ( j = 0; j < list2_size; ++j )
    result[j + list1_size - 1] = list2[j];
}