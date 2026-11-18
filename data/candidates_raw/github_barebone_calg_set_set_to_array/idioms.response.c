void *set_to_array(struct set *set)
{
  int i;
  int array_counter;
  void **array;
  struct setentry *entry;
  if ( (array = (void **)malloc(set->entries * sizeof(void *))) == ((void *)0))
    return ((void *)0);
  array_counter = 0;
  for (i = 0; i < set->table_size; i++)
  {
    for (entry = set->table[i]; entry != ((void *)0); entry = entry->next)
    {
      array[array_counter] = entry->data;
      array_counter++;
    }
  }
  return array;
}