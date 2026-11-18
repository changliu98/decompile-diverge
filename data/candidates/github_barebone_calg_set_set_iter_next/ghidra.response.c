SetValue set_iter_next(SetIterator *iterator)

{
  Set *pSVar1;
  SetEntry *pSVar2;
  uint chain;
  SetEntry *current_entry;
  SetValue result;
  Set *set;
  SetIterator *iterator_local;
  SetValue local_10;
  
  pSVar1 = iterator->set;
  if (iterator->next_entry == (SetEntry *)0x0) {
    local_10 = (SetValue)0x0;
  }
  else {
    pSVar2 = iterator->next_entry;
    local_10 = pSVar2->data;
    if (pSVar2->next == (SetEntry *)0x0) {
      iterator->next_entry = (SetEntry *)0x0;
      chain = iterator->next_chain;
      do {
        chain = chain + 1;
        if (pSVar1->table_size <= chain) goto LAB_001009c1;
      } while (pSVar1->table[chain] == (SetEntry *)0x0);
      iterator->next_entry = pSVar1->table[chain];
LAB_001009c1:
      iterator->next_chain = chain;
    }
    else {
      iterator->next_entry = pSVar2->next;
    }
  }
  return local_10;
}