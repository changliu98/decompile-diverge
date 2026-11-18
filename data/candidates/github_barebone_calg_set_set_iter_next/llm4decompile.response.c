SetValue set_iter_next(SetIterator *iterator)
{
  Set *set;
  SetValue result;
  unsigned int chain;

  set = iterator->set;
  if (iterator->next_entry == NULL) return NULL;

  result = iterator->next_entry->data;
  if (iterator->next_entry->next != NULL) {
    iterator->next_entry = iterator->next_entry->next;
  } else {
    chain = iterator->next_chain + 1;
    iterator->next_entry = NULL;
    while (chain < set->table_size) {
      if (set->table[chain] != NULL) {
        iterator->next_entry = set->table[chain];
        break;
      }
      chain++;
    }
    iterator->next_chain = chain;
  }
  return result;
}