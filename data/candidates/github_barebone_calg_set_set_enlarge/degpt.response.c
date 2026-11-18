int set_enlarge(Set *set)

{
  uint uVar1;
  SetEntry **__ptr;
  SetEntry *pSVar2;
  ulong uVar3;
  int iVar4;
  uint uVar5;
  uint i;
  uint index;
  uint old_prime_index;
  uint old_table_size;
  SetEntry **old_table;
  SetEntry *next;
  SetEntry *rover;
  Set *set_local;
  int local_c;
  
  __ptr = set->table;
  uVar1 = set->table_size;
  uVar5 = set->prime_index;
  set->prime_index = set->prime_index + 1;
  iVar4 = set_allocate_table(set);
  if (iVar4 == 0) {
    set->table = __ptr;
    set->table_size = uVar1;
    set->prime_index = uVar5;
    local_c = 0;
  }
  else {
    for (i = 0; i < uVar1; i = i + 1) {
      rover = __ptr[i];
      while (rover != (SetEntry *)0x0) {
        pSVar2 = rover->next;
        uVar5 = (*set->hash_func)(rover->data);
        uVar3 = (ulong)uVar5 % (ulong)set->table_size;
        rover->next = set->table[uVar3];
        set->table[uVar3] = rover;
        rover = pSVar2;
      }
    }
    free(__ptr);
    local_c = 1;
  }
  return local_c;
}