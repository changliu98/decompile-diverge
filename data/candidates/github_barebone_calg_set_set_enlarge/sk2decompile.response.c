static int set_enlarge(Set *set) {
  unsigned int i;
  unsigned int index;
  unsigned int old_size;
  SetEntry **old_table;
  unsigned int old_table_size;
  SetEntry *entry;
  SetEntry *next;
  old_table = set->table;
  old_table_size = set->table_size;
  old_size = set->size;
  set->size++;
  if (set_allocate_table(set) == 0) {
    set->table = old_table;
    set->table_size = old_table_size;
    set->size = old_size;
    return 0;
  }
  for (i = 0; i < old_table_size; i++) {
    entry = old_table[i];
    while (entry != NULL) {
      next = entry->next;
      index = set->hash_value(entry->data) % set->table_size;
      entry->next = set->table[index];
      set->table[index] = entry;
      entry = next;
    }
  }
  free(old_table);
  return 1;
}