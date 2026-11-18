struct _jwHashTable *create_hash(unsigned long buckets)
{
    struct _jwHashTable *table = (jwHashTable *)malloc(sizeof(jwHashTable));
    if (!table)
        return ((void *)0);
    table->bucket = (struct _jwHashEntry **)malloc(sizeof(jwHashEntry *) * buckets);
    if (!table->bucket) {
        free(table);
        return ((void *)0);
    }
    memset(table->bucket, 0, sizeof(struct _jwHashEntry *) * buckets);
    table->bucketsinitial = buckets;
    table->buckets = buckets;
    return table;
}