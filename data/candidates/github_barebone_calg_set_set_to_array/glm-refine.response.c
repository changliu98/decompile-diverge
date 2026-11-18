SetValue *__cdecl set_to_array(Set *set)
{
  SetValue *array;
  SetEntry *rover;
  size_t i;
  int array_counter;

  // Allocate memory for the array based on the number of entries in the set
  array = (SetValue *)malloc(sizeof(SetValue) * set->entries);
  if (array == NULL)
  {
    return NULL;
  }

  array_counter = 0;

  // Iterate over all buckets in the hash table
  for (i = 0; i < set->table_size; ++i)
  {
    // Traverse the linked list in each bucket
    for (rover = set->table[i]; rover != NULL; rover = rover->next)
    {
      array[array_counter++] = rover->data;
    }
  }

  return array;
}