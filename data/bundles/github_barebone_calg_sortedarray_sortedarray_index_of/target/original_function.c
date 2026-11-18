int sortedarray_index_of(SortedArray *sortedarray, SortedArrayValue data)
{
	unsigned int left, right, index;
	int order;

	if (sortedarray == NULL) {
		return -1;
	}

	left = 0;
	right = sortedarray->length;
	index = 0;

	/* safe subtract 1 of right without going negative */
	right = (right > 1) ? right : 0;

	while (left != right) {
		index = (left + right) / 2;
		order = sortedarray->cmp_func(data, sortedarray->data[index]);

		if (order < 0) {
			/* value should be left */
			right = index;
		} else if (order > 0) {
			/* value should be right */
			left = index + 1;
		} else {
			return (int) index;
		}
	}

	return -1;
}