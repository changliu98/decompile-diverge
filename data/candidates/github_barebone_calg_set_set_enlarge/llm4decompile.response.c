int set_enlarge(Set *set)
{
 unsigned int old_table_size;
 SetEntry **old_table;
 unsigned int old_prime_index;
 unsigned int index;
 SetEntry *rover;
 SetEntry *next;




 old_table = set->table;
 old_table_size = set->table_size;
 old_prime_index = set->prime_index;




 set->prime_index++;




 if (!set_allocate_table(set)) {
  set->table = old_table;
  set->table_size = old_table_size;
  set->prime_index = old_prime_index;

  return 0;
 }




 for (index = 0; index < old_table_size; index++) {




  rover = old_table[index];

  while (rover != NULL) {
   next = rover->next;




   index = set->hash_func(rover->data) % set->table_size;

   rover->next = set->table[index];
   set->table[index] = rover;




   rover = next;
  }
 }




 free(old_table);




 return 1;
}