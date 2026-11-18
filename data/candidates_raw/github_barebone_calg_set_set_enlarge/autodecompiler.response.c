int set_expand(Set *s)
{
 unsigned int i;
 unsigned int index;
 unsigned int old_table_size;
 unsigned int old_prime_index;
 SetItem **old_table;
 SetItem *rover;
 SetItem *next;
 int result;

 old_table = s->table;
 old_table_size = s->table_size;
 old_prime_index = s->prime_index;

 s->prime_index++;
 if (!set_allocate_table(s)) {
  s->table = old_table;
  s->table_size = old_table_size;
  s->prime_index = old_prime_index;
  result = 0;
 } else {
  for (i = 0; i < old_table_size; i++) {
   rover = old_table[i];
   while (rover != NULL) {
    next = rover->next;
    index = s->hash(rover->key) % s->table_size;
    rover->next = s->table[index];
    s->table[index] = rover;
    rover = next;
   }
  }
  free(old_table);
  result = 1;
 }

 return result;
}