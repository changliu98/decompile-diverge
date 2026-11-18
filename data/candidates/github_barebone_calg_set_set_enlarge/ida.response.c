int __cdecl set_enlarge(Set *set)
{
  unsigned int i; // [rsp+8h] [rbp-38h]
  unsigned int index; // [rsp+Ch] [rbp-34h]
  unsigned int old_prime_index; // [rsp+10h] [rbp-30h]
  unsigned int old_table_size; // [rsp+14h] [rbp-2Ch]
  SetEntry **old_table; // [rsp+18h] [rbp-28h]
  SetEntry *next; // [rsp+20h] [rbp-20h]
  SetEntry *rover; // [rsp+28h] [rbp-18h]

  old_table = set->table;
  old_table_size = set->table_size;
  old_prime_index = set->prime_index;
  set->prime_index = old_prime_index + 1;
  if ( set_allocate_table(set) )
  {
    for ( i = 0; i < old_table_size; ++i )
    {
      for ( rover = old_table[i]; rover; rover = next )
      {
        next = rover->next;
        index = set->hash_func(rover->data) % set->table_size;
        rover->next = set->table[index];
        set->table[index] = rover;
      }
    }
    free(old_table);
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