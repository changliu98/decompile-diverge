void __cdecl arraylist_sort_internal(
        ArrayListValue *list_data,
        unsigned int list_length,
        ArrayListCompareFunc compare_func)
{
  unsigned int list1_length; // [rsp+10h] [rbp-30h]
  unsigned int i; // [rsp+14h] [rbp-2Ch]
  ArrayListValue tmp; // [rsp+18h] [rbp-28h]
  ArrayListValue pivot; // [rsp+20h] [rbp-20h]

  if ( list_length > 1 )
  {
    pivot = list_data[list_length - 1];
    list1_length = 0;
    for ( i = 0; i < list_length - 1; ++i )
    {
      if ( compare_func(list_data[i], pivot) < 0 )
      {
        tmp = list_data[i];
        list_data[i] = list_data[list1_length];
        list_data[list1_length++] = tmp;
      }
    }
    list_data[list_length - 1] = list_data[list1_length];
    list_data[list1_length] = pivot;
    arraylist_sort_internal(list_data, list1_length, compare_func);
    arraylist_sort_internal(&list_data[list1_length + 1], list_length - list1_length - 1, compare_func);
  }
}