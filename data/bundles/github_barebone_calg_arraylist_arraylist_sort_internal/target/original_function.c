static void arraylist_sort_internal(ArrayListValue *list_data,
                                    unsigned int list_length,
                                    ArrayListCompareFunc compare_func)
{
	ArrayListValue pivot;
	ArrayListValue tmp;
	unsigned int i;
	unsigned int list1_length;
	unsigned int list2_length;

	/* If less than two items, it is always sorted. */
	if (list_length <= 1) {
		return;
	}

	/* Take the last item as the pivot. */
	pivot = list_data[list_length - 1];

	/* Divide the list into two lists:
	 *
	 * List 1 contains data less than the pivot.
	 * List 2 contains data more than the pivot.
	 *
	 * As the lists are build up, they are stored sequentially after
	 * each other, ie. list_data[list1_length-1] is the last item
	 * in list 1, list_data[list1_length] is the first item in
	 * list 2.
	 */
	list1_length = 0;

	for (i = 0; i < list_length - 1; ++i) {

		if (compare_func(list_data[i], pivot) < 0) {

			/* This should be in list 1.  Therefore it is in the
			 * wrong position. Swap the data immediately following
			 * the last item in list 1 with this data. */
			tmp = list_data[i];
			list_data[i] = list_data[list1_length];
			list_data[list1_length] = tmp;

			++list1_length;

		} else {
			/* This should be in list 2.  This is already in the
			 * right position. */
		}
	}

	/* The length of list 2 can be calculated. */
	list2_length = list_length - list1_length - 1;

	/* list_data[0..list1_length-1] now contains all items which are
	 * before the pivot.
	 * list_data[list1_length..list_length-2] contains all items after
	 * or equal to the pivot.
	 * Move the pivot into place, by swapping it with the item
	 * immediately following the end of list 1. */
	list_data[list_length - 1] = list_data[list1_length];
	list_data[list1_length] = pivot;

	/* Recursively sort the sublists. */
	arraylist_sort_internal(list_data, list1_length, compare_func);

	arraylist_sort_internal(&list_data[list1_length + 1], list2_length,
	                        compare_func);
}