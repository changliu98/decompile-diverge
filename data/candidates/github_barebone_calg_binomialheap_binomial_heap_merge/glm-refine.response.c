int __cdecl binomial_heap_merge(BinomialHeap *heap, BinomialHeap *other) {
    unsigned int max_length = (heap->roots_length > other->roots_length) 
                              ? heap->roots_length 
                              : other->roots_length;
    unsigned int max = max_length + 1;
    
    BinomialTree **new_roots = (BinomialTree **)malloc(sizeof(BinomialTree *) * max);
    if (!new_roots) {
        return 0;
    }

    unsigned int new_roots_length = 0;
    BinomialTree *carry = NULL;

    for (unsigned int i = 0; i < max; ++i) {
        int num_vals = 0;
        BinomialTree *vals[3] = {0};

        if (i < heap->roots_length && heap->roots[i]) {
            vals[num_vals++] = heap->roots[i];
        }
        if (i < other->roots_length && other->roots[i]) {
            vals[num_vals++] = other->roots[i];
        }
        if (carry) {
            vals[num_vals++] = carry;
        }

        // If there is an odd number of trees at this order, one becomes a root
        if (num_vals & 1) {
            new_roots[i] = vals[num_vals - 1];
            binomial_tree_ref(new_roots[i]);
            new_roots_length = i + 1;
        } else {
            new_roots[i] = NULL;
        }

        // If there are 2 or 3 trees, merge the first two to create a carry
        BinomialTree *new_carry = NULL;
        if (num_vals & 2) {
            new_carry = binomial_tree_merge(heap, vals[0], vals[1]);
            if (!new_carry) {
                binomial_heap_merge_undo(new_roots, i);
                binomial_tree_unref(carry);
                return 0;
            }
        }

        binomial_tree_unref(carry);
        carry = new_carry;
        if (new_carry) {
            binomial_tree_ref(new_carry);
        }
    }

    // Clean up the old heap roots
    for (unsigned int i = 0; i < heap->roots_length; ++i) {
        if (heap->roots[i]) {
            binomial_tree_unref(heap->roots[i]);
        }
    }
    
    free(heap->roots);
    heap->roots = new_roots;
    heap->roots_length = new_roots_length;

    return 1;
}