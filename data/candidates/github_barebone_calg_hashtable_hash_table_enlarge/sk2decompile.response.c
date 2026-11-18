static int hash_table_enlarge(hash_table_t *hash_table) {
  unsigned int old_size;
  unsigned int old_power;
  unsigned int i;
  hash_table_entry_t **old_table;
  hash_table_entry_t *entry;
  hash_table_entry_t *next;
  old_table = hash_table->table;
  old_size = hash_table->size;
  old_power = hash_table->power;
  hash_table->power++;
  if (hash_table_allocate_table(hash_table) == 0) {
    hash_table->table = old_table;
    hash_table->size = old_size;
    hash_table->power = old_power;
    return 0;
  }
  for (i = 0; i < old_size; i++) {
    entry = old_table[i];
    while (entry != NULL) {
      next = entry->next;
      unsigned int hash =
          hash_table->hash_func(entry->key.string) % hash_table->size;
      entry->next = hash_table->table[hash];
      hash_table->table[hash] = entry;
      entry = next;
    }
  }
  free(old_table);
  return 1;
}