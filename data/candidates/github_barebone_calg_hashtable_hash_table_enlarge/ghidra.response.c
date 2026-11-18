int hash_table_enlarge(HashTable *hash_table)

{
  uint uVar1;
  HashTableEntry **__ptr;
  HashTableEntry *pHVar2;
  ulong uVar3;
  int iVar4;
  uint uVar5;
  uint i;
  uint index;
  HashTableEntry *next;
  HashTablePair *pair;
  HashTableEntry *rover;
  uint old_prime_index;
  uint old_table_size;
  HashTableEntry **old_table;
  HashTable *hash_table_local;
  int local_c;
  
  __ptr = hash_table->table;
  uVar1 = hash_table->table_size;
  uVar5 = hash_table->prime_index;
  hash_table->prime_index = hash_table->prime_index + 1;
  iVar4 = hash_table_allocate_table(hash_table);
  if (iVar4 == 0) {
    hash_table->table = __ptr;
    hash_table->table_size = uVar1;
    hash_table->prime_index = uVar5;
    local_c = 0;
  }
  else {
    for (i = 0; i < uVar1; i = i + 1) {
      rover = __ptr[i];
      while (rover != (HashTableEntry *)0x0) {
        pHVar2 = rover->next;
        uVar5 = (*hash_table->hash_func)((rover->pair).key);
        uVar3 = (ulong)uVar5 % (ulong)hash_table->table_size;
        rover->next = hash_table->table[uVar3];
        hash_table->table[uVar3] = rover;
        rover = pHVar2;
      }
    }
    free(__ptr);
    local_c = 1;
  }
  return local_c;
}