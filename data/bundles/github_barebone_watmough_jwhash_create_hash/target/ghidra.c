jwHashTable * create_hash(size_t buckets)

{
  jwHashEntry **ppjVar1;
  jwHashTable *table;
  size_t buckets_local;
  jwHashTable *local_10;
  
  local_10 = malloc(0x20);
  if (local_10 == (jwHashTable *)0x0) {
    local_10 = (jwHashTable *)0x0;
  }
  else {
    ppjVar1 = malloc(buckets << 3);
    local_10->bucket = ppjVar1;
    if (local_10->bucket == (jwHashEntry **)0x0) {
      free(local_10);
      local_10 = (jwHashTable *)0x0;
    }
    else {
      memset(local_10->bucket,0,buckets << 3);
      local_10->bucketsinitial = buckets;
      local_10->buckets = buckets;
    }
  }
  return local_10;
}