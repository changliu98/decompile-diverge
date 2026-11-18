BinomialHeapValue binomial_heap_pop(BinomialHeap *heap)
{
	BinomialTree *least_tree;
	BinomialHeap fake_heap;
	BinomialHeapValue result;
	unsigned int i;
	unsigned int least_index;

	if (heap->num_values == 0) {
		return binomial_heap_null_value;
	}

	/* Find the tree with the lowest root value */
	least_index = UINT_MAX;

	for (i = 0; i < heap->roots_length; ++i) {

		if (heap->roots[i] == NULL) {
			continue;
		}

		if (least_index == UINT_MAX ||
		    binomial_heap_cmp(heap, heap->roots[i]->value,
		                      heap->roots[least_index]->value) < 0) {
			least_index = i;
		}
	}

	/* Remove the least_tree from the heap. */
	least_tree = heap->roots[least_index];
	heap->roots[least_index] = NULL;

	/* Construct a fake heap containing the data in the least tree */
	fake_heap.heap_type = heap->heap_type;
	fake_heap.compare_func = heap->compare_func;
	fake_heap.roots = least_tree->subtrees;
	fake_heap.roots_length = least_tree->order;

	/* Merge subtrees of least tree back into the heap */
	if (binomial_heap_merge(heap, &fake_heap)) {

		/* Merge successful */
		/* Remove reference to least tree */
		result = least_tree->value;
		binomial_tree_unref(least_tree);

		/* Update the number of values */
		--heap->num_values;

		return result;

	} else {

		/* Add the least tree back */
		heap->roots[least_index] = least_tree;

		/* Pop failed */
		return binomial_heap_null_value;
	}
}