static int set_enlarge(Set *set)
{
	SetEntry *rover;
	SetEntry *next;
	SetEntry **old_table;
	unsigned int old_table_size;
	unsigned int old_prime_index;
	unsigned int index;
	unsigned int i;

	/* Store the old table */
	old_table = set->table;
	old_table_size = set->table_size;
	old_prime_index = set->prime_index;

	/* Use the next table size from the prime number array */
	++set->prime_index;

	/* Allocate the new table */
	if (!set_allocate_table(set)) {
		set->table = old_table;
		set->table_size = old_table_size;
		set->prime_index = old_prime_index;

		return 0;
	}

	/* Iterate through all entries in the old table and add them
	 * to the new one */
	for (i = 0; i < old_table_size; ++i) {

		/* Walk along this chain */
		rover = old_table[i];

		while (rover != NULL) {

			next = rover->next;

			/* Hook this entry into the new table */
			index = set->hash_func(rover->data) % set->table_size;
			rover->next = set->table[index];
			set->table[index] = rover;

			/* Advance to the next entry in the chain */
			rover = next;
		}
	}

	/* Free back the old table */
	free(old_table);

	/* Resized successfully */
	return 1;
}