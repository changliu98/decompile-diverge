BinomialHeapValue binomial_heap_pop(BinomialHeap *heap)
{
 BinomialHeapValue result;
 int i;
 int least_index;
 BinomialTree *least_tree;
 BinomialHeap fake_heap;

 if (heap->num_values == 0) {
  return NULL;
 }

 least_index = -1;
 for (i = 0; i < heap->roots_length; i++) {
  if (heap->roots[i] == NULL) {
   continue;
  }
  if (least_index == -1 || binomial_heap_cmp(heap, heap->roots[i]->value, heap->roots[least_index]->value) < 0) {
   least_index = i;
  }
 }

 least_tree = heap->roots[least_index];
 heap->roots[least_index] = NULL;

 fake_heap.heap_type = heap->heap_type;
 fake_heap.compare_func = heap->compare_func;
 fake_heap.roots = least_tree->subtrees;
 fake_heap.roots_length = least_tree->order;

 if (!binomial_heap_merge(heap, &fake_heap)) {
  heap->roots[least_index] = least_tree;
  return NULL;
 }

 result = least_tree->value;
 binomial_tree_unref(least_tree);
 heap->num_values--;
 return result;
}