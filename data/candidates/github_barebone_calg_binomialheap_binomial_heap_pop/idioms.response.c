void *binomial_heap_pop(struct _binomial_heap *heap) {
  struct _binomial_tree *min;
  struct _binomial_heap fake;
  void *ret;
  if (heap->num_values == 0) {
    return ((void *)0);
  }
  unsigned int min_index = -1;
  for (unsigned int i = 0; i < heap->roots_length; i++) {
    if (heap->roots[i] == ((void *)0)) {
      continue;
    }
    if (min_index == -1 ||
        binomial_tree_compare(heap, heap->roots[i]->value,
                              heap->roots[min_index]->value) < 0) {
      min_index = i;
    }
  }
  min = heap->roots[min_index];
  heap->roots[min_index] = ((void *)0);
  fake.heap_type = heap->heap_type;
  fake.compare_func = heap->compare_func;
  fake.roots = min->subtrees;
  fake.roots_length = min->order;
  if (binomial_heap_merge(heap, &fake)) {
    ret = min->value;
    binomial_tree_free(min);
    heap->num_values--;
    return ret;
  }
  heap->roots[min_index] = min;
  return ((void *)0);
}