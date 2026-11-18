int set_enlarge(struct set *set)
{
  struct setentry *rover; struct setentry *next;
  struct setentry **old_table;
  unsigned int old_table_size;
  unsigned int old_prime_index;
  unsigned int index;
  old_table = set->table;
  old_table_size = set->table_size;
  old_prime_index = set->prime_index;
  set->prime_index = old_prime_index + 1;
  if (set_rehash_table(set))
  {
    for (index = 0; index < old_table_size; index++)
    {
      for (rover = old_table[index]; rover != ((void *)0); rover = next)
      {
        next = rover->next;
        index = set->hash_func(rover->data) % set->table_size;
        rover->next = set->table[index];
        set->table[index] = rover;
      }
    }
    set_free_table(old_table);
    return 1;
  }
  else
  {
    set->table = old_table;
    set->table_size = old_table_size;
    set->prime_index = old_prime_index;
    return 0;
  }
}