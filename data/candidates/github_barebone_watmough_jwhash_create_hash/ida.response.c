jwHashTable *__cdecl create_hash(size_t buckets)
{
  jwHashTable *table; // [rsp+8h] [rbp-18h]

  table = (jwHashTable *)malloc(0x20uLL);
  if ( !table )
    return 0LL;
  table->bucket = (jwHashEntry **)malloc(8 * buckets);
  if ( table->bucket )
  {
    memset(table->bucket, 0, 8 * buckets);
    table->bucketsinitial = buckets;
    table->buckets = buckets;
    return table;
  }
  else
  {
    free(table);
    return 0LL;
  }
}