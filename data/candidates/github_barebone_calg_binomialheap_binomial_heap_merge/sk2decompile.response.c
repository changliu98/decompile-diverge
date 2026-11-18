int binomial_heap_merge(BinomialHeap *heap, BinomialHeap *other) {
  unsigned int max_order =
      (heap->order > other->order) ? heap->order : other->order;
  unsigned int new_order = max_order + 1;
  BinomialTree **new_trees = malloc(sizeof(BinomialTree *) * new_order);
  if (!new_trees) return 0;
  unsigned int new_heap_order = 0;
  BinomialTree *carry = NULL;
  for (unsigned int i = 0; i < new_order; i++) {
    unsigned int num_trees = 0;
    BinomialTree *trees[3];
    if (i < heap->order && heap->trees[i]) {
      trees[0] = heap->trees[i];
      num_trees++;
    }
    if (i < other->order && other->trees[i]) {
      trees[num_trees] = other->trees[i];
      num_trees++;
    }
    if (carry) {
      trees[num_trees] = carry;
      num_trees++;
    }
    if (num_trees % 2) {
      new_trees[i] = trees[num_trees - 1];
      binomial_tree_ref(new_trees[i]);
      new_heap_order = i + 1;
    } else {
      new_trees[i] = NULL;
    }
    BinomialTree *new_carry;
    if (num_trees % 2) {
      new_carry = binomial_tree_merge(heap, trees[0], trees[1]);
      if (!new_carry) {
        binomial_heap_merge_undo(new_trees, i);
        binomial_tree_unref(carry);
        return 0;
      }
    } else {
      new_carry = NULL;
    }
    binomial_tree_unref(carry);
    carry = new_carry;
    binomial_tree_ref(carry);
  }
  for (unsigned int i = 0; i < heap->order; i++) {
    if (heap->trees[i]) binomial_tree_unref(heap->trees[i]);
  }
  free(heap->trees);
  heap->trees = new_trees;
  heap->order = new_heap_order;
  return 1;
}