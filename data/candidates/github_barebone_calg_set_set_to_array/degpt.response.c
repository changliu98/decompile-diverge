SetValue * set_to_array(Set *set)

{
  SetEntry *rover;
  uint i;
  int array_counter;
  SetValue *array;
  Set *set_local;
  SetValue *local_10;
  
  local_10 = malloc((ulong)set->entries << 3);
  if (local_10 == (SetValue *)0x0) {
    local_10 = (SetValue *)0x0;
  }
  else {
    array_counter = 0;
    for (i = 0; i < set->table_size; i = i + 1) {
      for (rover = set->table[i]; rover != (SetEntry *)0x0; rover = rover->next) {
        local_10[array_counter] = rover->data;
        array_counter = array_counter + 1;
      }
    }
  }
  return local_10;
}