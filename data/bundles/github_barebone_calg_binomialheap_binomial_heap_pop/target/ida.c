BinomialHeapValue __cdecl binomial_heap_pop(BinomialHeap *heap)
{
  unsigned int least_index; // [rsp+0h] [rbp-50h]
  unsigned int i; // [rsp+4h] [rbp-4Ch]
  BinomialHeapValue result; // [rsp+8h] [rbp-48h]
  BinomialHeap fake_heap; // [rsp+10h] [rbp-40h] BYREF
  BinomialTree *least_tree; // [rsp+38h] [rbp-18h]
  BinomialHeap *heapa; // [rsp+40h] [rbp-10h]

  heapa = heap;
  if ( !heap->num_values )
    return 0LL;
  least_index = -1;
  for ( i = 0; i < heapa->roots_length; ++i )
  {
    if ( heapa->roots[i]
      && (least_index == -1 || binomial_heap_cmp(heapa, heapa->roots[i]->value, heapa->roots[least_index]->value) < 0) )
    {
      least_index = i;
    }
  }
  least_tree = heapa->roots[least_index];
  heapa->roots[least_index] = 0LL;
  fake_heap.heap_type = heapa->heap_type;
  fake_heap.compare_func = heapa->compare_func;
  fake_heap.roots = least_tree->subtrees;
  fake_heap.roots_length = least_tree->order;
  if ( binomial_heap_merge(heapa, &fake_heap) )
  {
    result = least_tree->value;
    binomial_tree_unref(least_tree);
    --heapa->num_values;
    return result;
  }
  else
  {
    heapa->roots[least_index] = least_tree;
    return 0LL;
  }
}