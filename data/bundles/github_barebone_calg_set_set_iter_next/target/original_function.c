SetValue set_iter_next(SetIterator *iterator)
{
	Set *set;
	SetValue result;
	SetEntry *current_entry;
	unsigned int chain;

	set = iterator->set;

	/* No more entries? */
	if (iterator->next_entry == NULL) {
		return set_null_value;
	}

	/* We have the result immediately */
	current_entry = iterator->next_entry;
	result = current_entry->data;

	/* Advance next_entry to the next SetEntry in the Set. */
	if (current_entry->next != NULL) {

		/* Use the next value in this chain */
		iterator->next_entry = current_entry->next;

	} else {

		/* Default value if no valid chain is found */
		iterator->next_entry = NULL;

		/* No more entries in this chain.  Search the next chain */
		chain = iterator->next_chain + 1;

		while (chain < set->table_size) {

			/* Is there a chain at this table entry? */
			if (set->table[chain] != NULL) {

				/* Valid chain found! */
				iterator->next_entry = set->table[chain];

				break;
			}

			/* Keep searching until we find an empty chain */
			++chain;
		}

		iterator->next_chain = chain;
	}

	return result;
}