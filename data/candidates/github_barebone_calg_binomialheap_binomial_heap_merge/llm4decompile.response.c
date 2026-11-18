bool binomial_heap_merge(BinomialHeap *heap, BinomialHeap *other)
{
    unsigned int max = heap->roots_length > other->roots_length ? heap->roots_length : other->roots_length;
    BinomialTree **new_roots = malloc((max + 1) * sizeof(BinomialTree *));
    if (new_roots == NULL)
        return false;

    unsigned int new_roots_length = 0;
    BinomialTree *carry = NULL;
    for (unsigned int i = 0; i < max + 1; i++) {
        BinomialTree *vals[3];
        unsigned int num_vals = 0;
        if (i < heap->roots_length && heap->roots[i] != NULL)
            vals[num_vals++] = heap->roots[i];
        if (i < other->roots_length && other->roots[i] != NULL)
            vals[num_vals++] = other->roots[i];
        if (carry != NULL)
            vals[num_vals++] = carry;

        if (num_vals % 2 == 0) {
            new_roots[i] = NULL;
        } else {
            new_roots[i] = vals[num_vals - 1];
            binomial_tree_ref(new_roots[i]);
            new_roots_length = i + 1;
        }

        BinomialTree *new_carry = NULL;
        if (num_vals >= 2) {
            new_carry = binomial_tree_merge(heap, vals[0], vals[1]);
            if (new_carry == NULL) {
                binomial_heap_merge_undo(new_roots, i);
                binomial_tree_unref(carry);
                return false;
            }
        }

        binomial_tree_unref(carry);
        carry = new_carry;
        binomial_tree_ref(carry);
    }

    for (unsigned int i = 0; i < heap->roots_length; i++)
        if (heap->roots[i] != NULL)
            binomial_tree_unref(heap->roots[i]);
    free(heap->roots);
    heap->roots = new_roots;
    heap->roots_length = new_roots_length;

    return true;
}