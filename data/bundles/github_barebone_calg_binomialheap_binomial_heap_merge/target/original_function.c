static int binomial_heap_merge(BinomialHeap *heap, BinomialHeap *other)
{
	BinomialTree **new_roots;
	unsigned int new_roots_length;
	BinomialTree *vals[3];
	int num_vals;
	BinomialTree *carry;
	BinomialTree *new_carry;
	unsigned int max;
	unsigned int i;

	/* Find the maximum length of the two heaps.  Add one because
	 * after merging we may have one more value to carry over. */
	if (heap->roots_length > other->roots_length) {
		max = heap->roots_length + 1;
	} else {
		max = other->roots_length + 1;
	}

	/* Allocate an array for the new roots */
	new_roots = malloc(sizeof(BinomialTree *) * max);

	if (new_roots == NULL) {
		return 0;
	}

	/* Go through one entry at a time.  This works kind of like a
	 * ripple-carry adder. */
	new_roots_length = 0;
	carry = NULL;

	for (i = 0; i < max; ++i) {

		/* Build up 'vals' as a list of all the values we must
		 * merge at this step. */
		num_vals = 0;

		/* If there is a value in 'heap', add it */
		if (i < heap->roots_length && heap->roots[i] != NULL) {
			vals[num_vals] = heap->roots[i];
			++num_vals;
		}

		/* If there is a value in 'other', add it */
		if (i < other->roots_length && other->roots[i] != NULL) {
			vals[num_vals] = other->roots[i];
			++num_vals;
		}

		/* If there is a carried value from the previous iteration,
		 * add it */
		if (carry != NULL) {
			vals[num_vals] = carry;
			++num_vals;
		}

		/* When num_vals == 1 or 3, we store a value. */
		if ((num_vals & 1) != 0) {

			/* Save the last value into new_roots. */
			new_roots[i] = vals[num_vals - 1];
			binomial_tree_ref(new_roots[i]);
			new_roots_length = i + 1;

		} else {

			/* No value to store at this iteration */
			new_roots[i] = NULL;
		}

		/* When num_vals == 2 or 3, we must carry over to the
		 * next iteration */
		if ((num_vals & 2) != 0) {

			/* Merge the first two values and carry to the
			 * next iteration */
			new_carry = binomial_tree_merge(heap, vals[0], vals[1]);

			if (new_carry == NULL) {

				/* Remove references that we have added
				 * (freeing any BinomialTree structures
				 * that were created in the process) */
				binomial_heap_merge_undo(new_roots, i);

				/* Unreference the carry variable */
				binomial_tree_unref(carry);

				return 0;
			}

		} else {

			/* Nothing to carry */
			new_carry = NULL;
		}

		/* Unreference previous carried value */
		binomial_tree_unref(carry);

		/* Assign the new value of carry, and add a reference */
		carry = new_carry;

		binomial_tree_ref(carry);
	}

	/* Unreference all values in the old 'roots' array, freeing unused
	 * BinomialTree structures as necessary. */
	for (i = 0; i < heap->roots_length; ++i) {
		if (heap->roots[i] != NULL) {
			binomial_tree_unref(heap->roots[i]);
		}
	}

	/* Free the old roots array and use the new one */
	free(heap->roots);
	heap->roots = new_roots;
	heap->roots_length = new_roots_length;

	/* Merged successfully */
	return 1;
}