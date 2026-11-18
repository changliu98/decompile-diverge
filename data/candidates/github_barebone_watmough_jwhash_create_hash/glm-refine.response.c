jwHashTable *create_hash(size_t buckets)
{
    jwHashTable *table = (jwHashTable *)malloc(sizeof(jwHashTable));
    if (!table)
        return NULL;

    table->bucket = (jwHashEntry **)malloc(sizeof(jwHashEntry *) * buckets);
    if (table->bucket)
    {
        memset(table->bucket, 0, sizeof(jwHashEntry *) * buckets);
        table->bucketsinitial = buckets;
        table->buckets = buckets;
        return table;
    }

    free(table);
    return NULL;
}