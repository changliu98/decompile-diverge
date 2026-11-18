int binomial_heap_merge(struct BinomialHeap *heap1, struct BinomialHeap *heap2) {
    // Determine the maximum possible size for the new trees array
    unsigned int max_size = (heap1->size > heap2->size ? heap1->size : heap2->size) + 1;
    
    // Allocate new array of tree pointers
    struct BinomialTree **new_trees = malloc(max_size * sizeof(struct BinomialTree *));
    if (!new_trees) {
        return 0;
    }

    unsigned int new_size = 0;
    struct BinomialTree *carry = NULL;

    // Merge the heaps bit-by-bit (like binary addition)
    for (unsigned int i = 0; i < max_size; i++) {
        int count = 0;
        struct BinomialTree *trees[3];

        // Collect existing trees of order i
        if (i < heap1->size && heap1->trees[i] != NULL) {
            trees[count++] = heap1->trees[i];
        }
        if (i < heap2->size && heap2->trees[i] != NULL) {
            trees[count++] = heap2->trees[i];
        }
        if (carry != NULL) {
            trees[count++] = carry;
        }

        // If exactly one tree, place it in the current slot
        if ((count & 1) != 0) {
            new_trees[i] = trees[count - 1];
            new_size = i + 1;
        } else {
            new_trees[i] = NULL;
        }

        // If two or more trees, merge them to create a carry for the next iteration
        if ((count & 2) != 0) {
            carry = binomial_tree_merge(heap1, trees[0], trees[1]);
            if (!carry) {
                // On failure, rollback the merge operation
                binomial_heap_merge_undo(new_trees, i, carry);
                binomial_tree_unref(carry); // Unref the NULL carry (likely a no-op macro)
                return 0;
            }
        } else {
            carry = NULL;
        }
    }

    // Cleanup old heap1 trees and update heap1 with the newly merged trees
    for (unsigned int i = 0; i < heap1->size; i++) {
        if (heap1->trees[i] != NULL) {
            binomial_tree_unref(heap1->trees[i]);
        }
    }
    free(heap1->trees);
    
    heap1->trees = new_trees;
    heap1->size = new_size;

    return 1;
}