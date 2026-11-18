jwHashTable *create_hash(size_t buckets)
{
 jwHashTable *table;

 if( (table = malloc(sizeof(jwHashTable))) == NULL )
  return NULL;

 if( (table->bucket = malloc(buckets * sizeof(jwHashEntry *))) == NULL )
 {
  free(table);
  return NULL;
 }
 memset(table->bucket, 0, buckets * sizeof(jwHashEntry *));
 table->buckets = table->bucketsinitial = buckets;

 return table;
}