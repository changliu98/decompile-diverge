int binary_heap_insert(BinaryHeap *heap, BinaryHeapValue value)
{
	BinaryHeapValue *new_values;
	unsigned int index;
	unsigned int new_size;
	unsigned int parent;

	/* Possibly realloc the heap to a larger size */
	if (heap->num_values >= heap->alloced_size) {

		/* Double the table size */
		new_size = heap->alloced_size * 2;
		new_values =
		    realloc(heap->values, sizeof(BinaryHeapValue) * new_size);

		if (new_values == NULL) {
			return 0;
		}

		heap->alloced_size = new_size;
		heap->values = new_values;
	}

	/* Add to the bottom of the heap and start from there */
	index = heap->num_values;
	++heap->num_values;

	/* Percolate the value up to the top of the heap */
	while (index > 0) {

		/* The parent index is found by halving the node index */
		parent = (index - 1) / 2;

		/* Compare the node with its parent */
		if (binary_heap_cmp(heap, heap->values[parent], value) < 0) {

			/* Ordered correctly - insertion is complete */
			break;

		} else {

			/* Need to swap this node with its parent */
			heap->values[index] = heap->values[parent];

			/* Advance up to the parent */
			index = parent;
		}
	}

	/* Save the new value in the final location */
	heap->values[index] = value;

	return 1;
}