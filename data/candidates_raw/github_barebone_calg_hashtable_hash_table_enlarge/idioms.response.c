int hashtable_rehash(struct _HashTable *hashtable)
{
  struct _HashTableEntry *rover; struct _HashTableEntry *next;
  struct _HashTableEntry **old_table;
  unsigned int old_table_size;
  unsigned int old_prime_index;
  unsigned int index;
  old_table = hashtable->table;
  old_table_size = hashtable->table_size;
  old_prime_index = hashtable->prime_index;
  hashtable->prime_index = old_prime_index + 1;
  if (hashtable_rehash_alloc(hashtable))
  {
    for (index = 0; index < old_table_size; index++)
    {
      for (rover = old_table[index]; rover != ((void *)0); rover = next)
      {
        next = rover->next;
        index = hashtable->hash_func(rover->pair.key) % hashtable->table_size;
        rover->next = hashtable->table[index];
        hashtable->table[index] = rover;
      }
    }
    hashtable_rehash_free(old_table);
    return 1;
  }
  else
  {
    hashtable->table = old_table;
    hashtable->table_size = old_table_size;
    hashtable->prime_index = old_prime_index;
    return 0;
  }
}