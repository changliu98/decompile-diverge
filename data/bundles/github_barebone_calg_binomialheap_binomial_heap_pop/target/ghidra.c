BinomialHeapValue binomial_heap_pop(BinomialHeap *heap)

{
  BinomialTree *tree;
  int iVar1;
  uint least_index;
  uint i;
  BinomialHeapValue result;
  BinomialHeap fake_heap;
  BinomialTree *least_tree;
  BinomialHeap *heap_local;
  BinomialHeapValue local_10;
  
  if (heap->num_values == 0) {
    local_10 = (BinomialHeapValue)0x0;
  }
  else {
    least_index = 0xffffffff;
    for (i = 0; i < heap->roots_length; i = i + 1) {
      if ((heap->roots[i] != (BinomialTree *)0x0) &&
         ((least_index == 0xffffffff ||
          (iVar1 = binomial_heap_cmp(heap,heap->roots[i]->value,heap->roots[least_index]->value),
          iVar1 < 0)))) {
        least_index = i;
      }
    }
    tree = heap->roots[least_index];
    heap->roots[least_index] = (BinomialTree *)0x0;
    fake_heap.heap_type = heap->heap_type;
    fake_heap.compare_func = heap->compare_func;
    fake_heap.roots = tree->subtrees;
    fake_heap.roots_length = (uint)tree->order;
    iVar1 = binomial_heap_merge(heap,&fake_heap);
    if (iVar1 == 0) {
      heap->roots[least_index] = tree;
      local_10 = (BinomialHeapValue)0x0;
    }
    else {
      local_10 = tree->value;
      binomial_tree_unref(tree);
      heap->num_values = heap->num_values - 1;
    }
  }
  return local_10;
}