static int hash_table_enlarge(HashTable *hash_table)
{
	HashTableEntry **old_table;
	unsigned int old_table_size;
	unsigned int old_prime_index;
	HashTableEntry *rover;
	HashTablePair *pair;
	HashTableEntry *next;
	unsigned int index;
	unsigned int i;

	/* Store a copy of the old table */
	old_table = hash_table->table;
	old_table_size = hash_table->table_size;
	old_prime_index = hash_table->prime_index;

	/* Allocate a new, larger table */
	++hash_table->prime_index;

	if (!hash_table_allocate_table(hash_table)) {

		/* Failed to allocate the new table */
		hash_table->table = old_table;
		hash_table->table_size = old_table_size;
		hash_table->prime_index = old_prime_index;

		return 0;
	}

	/* Link all entries from all chains into the new table */
	for (i = 0; i < old_table_size; ++i) {
		rover = old_table[i];

		while (rover != NULL) {
			next = rover->next;

			/* Fetch rover HashTablePair */
			pair = &(rover->pair);

			/* Find the index into the new table */
			index = hash_table->hash_func(pair->key) %
			        hash_table->table_size;

			/* Link this entry into the chain */
			rover->next = hash_table->table[index];
			hash_table->table[index] = rover;

			/* Advance to next in the chain */
			rover = next;
		}
	}

	/* Free the old table */
	free(old_table);

	return 1;
}