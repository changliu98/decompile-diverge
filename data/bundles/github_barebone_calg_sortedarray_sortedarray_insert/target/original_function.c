int sortedarray_insert(SortedArray *sortedarray, SortedArrayValue data)
{
	unsigned int left, right, index;
	int order;

	if (sortedarray == NULL) {
		return 0;
	}

	left = 0;
	right = sortedarray->length;
	index = 0;

	/* When length is 1 set right to 0 so that the loop is not entered */
	right = (right > 1) ? right : 0;

	while (left != right) {
		index = (left + right) / 2;
		order = sortedarray->cmp_func(data, sortedarray->data[index]);

		if (order < 0) {
			/* value should be left of index */
			right = index;
		} else if (order > 0) {
			/* value should be right of index */
			left = index + 1;
		} else {
			/* value should be at index */
			break;
		}
	}

	/* look whether the item should be put before or after the index */
	if (sortedarray->length > 0 &&
	    sortedarray->cmp_func(data, sortedarray->data[index]) > 0) {
		index++;
	}

	/* insert element at index */
	if (sortedarray->length + 1 > sortedarray->_alloced) {
		/* enlarge the array */
		unsigned int newsize;
		SortedArrayValue *data;

		newsize = sortedarray->_alloced * 2;
		data = realloc(sortedarray->data,
		               sizeof(SortedArrayValue) * newsize);

		if (data == NULL) {
			return 0;
		} else {
			sortedarray->data = data;
			sortedarray->_alloced = newsize;
		}
	}

	/* move all other elements */
	memmove(&sortedarray->data[index + 1], &sortedarray->data[index],
	        (sortedarray->length - index) * sizeof(SortedArrayValue));

	/* insert entry */
	sortedarray->data[index] = data;
	++sortedarray->length;

	return 1;
}