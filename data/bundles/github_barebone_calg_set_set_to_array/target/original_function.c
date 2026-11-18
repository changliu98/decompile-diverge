SetValue *set_to_array(Set *set)
{
	SetValue *array;
	int array_counter;
	unsigned int i;
	SetEntry *rover;

	/* Create an array to hold the set entries */
	array = malloc(sizeof(SetValue) * set->entries);

	if (array == NULL) {
		return NULL;
	}

	array_counter = 0;

	/* Iterate over all entries in all chains */
	for (i = 0; i < set->table_size; ++i) {

		rover = set->table[i];

		while (rover != NULL) {

			/* Add this value to the array */
			array[array_counter] = rover->data;
			++array_counter;

			/* Advance to the next entry */
			rover = rover->next;
		}
	}

	return array;
}