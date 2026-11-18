void *binomial_heap_pop(struct binomial_heap *heap) {
    if (heap->num_entries == 0) {
        return NULL;
    }

    int min_index = -1;
    for (uint32_t i = 0; i < heap->capacity; i++) {
        if (heap->trees[i] != NULL) {
            if (min_index != -1) {
                void *key1 = heap->trees[i]->key;
                void *key2 = heap->trees[min_index]->key;
                if (binomial_heap_cmp(heap, key1, key2) < 0) {
                    min_index = i;
                }
            } else {
                min_index = i;
            }
        }
    }

    struct binomial_tree *min_tree = heap->trees[min_index];
    heap->trees[min_index] = NULL;

    struct binomial_tree_ref ref;
    ref.key = heap->field_0;
    ref.value = heap->field_8;
    ref.children = min_tree->parent;
    ref.order = min_tree->order;

    if (binomial_heap_merge_undo(heap, &ref) == 0) {
        // If the merge undo fails, restore the original tree
        heap->trees[min_index] = min_tree;
        return NULL;
    }

    void *min_key = min_tree->key;
    binomial_tree_free(min_tree);
    heap->num_entries--;

    return min_key;
}