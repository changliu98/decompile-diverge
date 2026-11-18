SetValue __cdecl set_iter_next(SetIterator *iterator)
{
  unsigned int chain; // [rsp+0h] [rbp-2Ch]
  SetEntry *current_entry; // [rsp+4h] [rbp-28h]
  SetValue result; // [rsp+Ch] [rbp-20h]
  Set *set; // [rsp+14h] [rbp-18h]

  set = iterator->set;
  if ( !iterator->next_entry )
    return 0LL;
  current_entry = iterator->next_entry;
  result = current_entry->data;
  if ( current_entry->next )
  {
    iterator->next_entry = current_entry->next;
  }
  else
  {
    iterator->next_entry = 0LL;
    for ( chain = iterator->next_chain + 1; chain < set->table_size; ++chain )
    {
      if ( set->table[chain] )
      {
        iterator->next_entry = set->table[chain];
        break;
      }
    }
    iterator->next_chain = chain;
  }
  return result;
}