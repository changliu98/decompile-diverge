bin_heap_key_t binomial_heap_pop(BinomialHeap *heap) {
  if (heap->size == 0) {
    return 0;
  }
  unsigned int min_index = -1;
  for (unsigned int i = 0; i < heap->trees_len; i++) {
    if (heap->trees[i] != NULL) {
      if (min_index == -1 || binomial_heap_cmp(heap, heap->trees[i]->key,
                                               heap->trees[min_index]->key) < 0) {
        min_index = i;
      }
    }
  }
  BinomialTree *min_tree = heap->trees[min_index];
  heap->trees[min_index] = NULL;
  BinomialHeap sub_heap = {.cmp = heap->cmp,
                           .key_free = heap->key_free,
                           .trees = min_tree->children,
                           .trees_len = min_tree->children_len};
  if (binomial_heap_merge(heap, &sub_heap)) {
    bin_heap_key_t key = min_tree->key;
    binomial_tree_unref(min_tree);
    heap->size--;
    return key;
  } else {
    heap->trees[min_index] = min_tree;
    return 0;
  }
}