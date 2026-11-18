int binomial_heap_merge(BinomialHeap *heap,BinomialHeap *other)

{
  uint uVar1;
  BinomialTree **new_roots_00;
  uint i;
  uint max;
  BinomialTree *new_carry;
  BinomialTree *carry;
  int num_vals;
  BinomialTree *vals [3];
  uint new_roots_length;
  BinomialTree **new_roots;
  BinomialHeap *other_local;
  BinomialHeap *heap_local;
  int local_c;
  
  if (other->roots_length < heap->roots_length) {
    uVar1 = heap->roots_length;
  }
  else {
    uVar1 = other->roots_length;
  }
  max = uVar1 + 1;
  new_roots_00 = malloc((ulong)max << 3);
  if (new_roots_00 == (BinomialTree **)0x0) {
    local_c = 0;
  }
  else {
    new_roots_length = 0;
    carry = (BinomialTree *)0x0;
    for (i = 0; i < max; i = i + 1) {
      num_vals = 0;
      if ((i < heap->roots_length) && (heap->roots[i] != (BinomialTree *)0x0)) {
        vals[0] = heap->roots[i];
        num_vals = 1;
      }
      if ((i < other->roots_length) && (other->roots[i] != (BinomialTree *)0x0)) {
        vals[num_vals] = other->roots[i];
        num_vals = num_vals + 1;
      }
      if (carry != (BinomialTree *)0x0) {
        vals[num_vals] = carry;
        num_vals = num_vals + 1;
      }
      if ((num_vals & 1U) == 0) {
        new_roots_00[i] = (BinomialTree *)0x0;
      }
      else {
        new_roots_00[i] = vals[num_vals + -1];
        binomial_tree_ref(new_roots_00[i]);
        new_roots_length = i + 1;
      }
      if ((num_vals & 2U) == 0) {
        new_carry = (BinomialTree *)0x0;
      }
      else {
        new_carry = binomial_tree_merge(heap,vals[0],vals[1]);
        if (new_carry == (BinomialTree *)0x0) {
          binomial_heap_merge_undo(new_roots_00,i);
          binomial_tree_unref(carry);
          return 0;
        }
      }
      binomial_tree_unref(carry);
      carry = new_carry;
      binomial_tree_ref(new_carry);
    }
    for (i = 0; i < heap->roots_length; i = i + 1) {
      if (heap->roots[i] != (BinomialTree *)0x0) {
        binomial_tree_unref(heap->roots[i]);
      }
    }
    free(heap->roots);
    heap->roots = new_roots_00;
    heap->roots_length = new_roots_length;
    local_c = 1;
  }
  return local_c;
}