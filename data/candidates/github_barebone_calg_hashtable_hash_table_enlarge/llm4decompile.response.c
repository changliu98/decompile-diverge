int hash_table_enlarge(HashTable *hash_table)
{
  HashTableEntry *rover;
  HashTableEntry *next;
  HashTableEntry **old_table;
  unsigned int old_table_size;
  unsigned int old_prime_index;
  unsigned int index;
  unsigned int i;


  old_table = hash_table->table;
  old_table_size = hash_table->table_size;
  old_prime_index = hash_table->prime_index;


  hash_table->prime_index++;


  if (!hash_table_allocate_table(hash_table))
    {

      hash_table->table = old_table;
      hash_table->table_size = old_table_size;
      hash_table->prime_index = old_prime_index;


      return 0;
    }


  for (i = 0; i < old_table_size; i++)
    {
      rover = old_table[i];

      while (rover != NULL)
        {
          next = rover->next;


          index = hash_table->hash_func(rover->pair.key) % hash_table->table_size;
          rover->next = hash_table->table[index];
          hash_table->table[index] = rover;


          rover = next;
        }
    }


  free(old_table);


  return 1;
}