jwHashTable *create_hash( size_t buckets )
{
	// allocate space
	jwHashTable *table= (jwHashTable *)malloc(sizeof(jwHashTable));
	if(!table) {
		// unable to allocate
		return NULL;
	}
	// locks
#ifdef HASHTHREADED
	table->lock = 0;
	table->locks = (int *)malloc(buckets * sizeof(int));
	if( !table->locks ) {
		free(table);
		return NULL;
	}
	memset((int *)&table->locks[0],0,buckets*sizeof(int));
#endif
	// setup
	table->bucket = (jwHashEntry **)malloc(buckets*sizeof(void*));
	if( !table->bucket ) {
		free(table);
		return NULL;
	}
	memset(table->bucket,0,buckets*sizeof(void*));
	table->buckets = table->bucketsinitial = buckets;
	HASH_DEBUG("table: %x bucket: %x\n",table,table->bucket);
	return table;
}