int __cdecl hash_table_enlarge(HashTable *hash_table)
{
  unsigned int i; // [rsp+0h] [rbp-40h]
  unsigned int index; // [rsp+4h] [rbp-3Ch]
  HashTableEntry *next; // [rsp+8h] [rbp-38h]
  HashTableEntry *rover; // [rsp+18h] [rbp-28h]
  unsigned int old_prime_index; // [rsp+20h] [rbp-20h]
  unsigned int old_table_size; // [rsp+24h] [rbp-1Ch]
  HashTableEntry **old_table; // [rsp+28h] [rbp-18h]

  old_table = hash_table->table;
  old_table_size = hash_table->table_size;
  old_prime_index = hash_table->prime_index;
  hash_table->prime_index = old_prime_index + 1;
  if ( hash_table_allocate_table(hash_table) )
  {
    for ( i = 0; i < old_table_size; ++i )
    {
      for ( rover = old_table[i]; rover; rover = next )
      {
        next = rover->next;
        index = hash_table->hash_func(rover->pair.key) % hash_table->table_size;
        rover->next = hash_table->table[index];
        hash_table->table[index] = rover;
      }
    }
    free(old_table);
    return 1;
  }
  else
  {
    hash_table->table = old_table;
    hash_table->table_size = old_table_size;
    hash_table->prime_index = old_prime_index;
    return 0;
  }
}