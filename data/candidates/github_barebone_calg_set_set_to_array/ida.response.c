SetValue *__cdecl set_to_array(Set *set)
{
  SetEntry *rover; // [rsp+8h] [rbp-28h]
  unsigned int i; // [rsp+10h] [rbp-20h]
  int array_counter; // [rsp+14h] [rbp-1Ch]
  SetValue *array; // [rsp+18h] [rbp-18h]

  array = (SetValue *)malloc(8LL * set->entries);
  if ( !array )
    return 0LL;
  array_counter = 0;
  for ( i = 0; i < set->table_size; ++i )
  {
    for ( rover = set->table[i]; rover; rover = rover->next )
      array[array_counter++] = rover->data;
  }
  return array;
}