int __cdecl binomial_heap_merge(BinomialHeap *heap, BinomialHeap *other)
{
  unsigned int roots_length; // eax
  unsigned int i; // [rsp+0h] [rbp-60h]
  unsigned int ia; // [rsp+0h] [rbp-60h]
  unsigned int max; // [rsp+4h] [rbp-5Ch]
  BinomialTree *new_carry; // [rsp+8h] [rbp-58h]
  BinomialTree *carry; // [rsp+10h] [rbp-50h]
  int num_vals; // [rsp+1Ch] [rbp-44h]
  BinomialTree *vals[3]; // [rsp+20h] [rbp-40h]
  unsigned int new_roots_length; // [rsp+3Ch] [rbp-24h]
  BinomialTree **new_roots; // [rsp+40h] [rbp-20h]
  BinomialHeap *othera; // [rsp+48h] [rbp-18h]
  BinomialHeap *heapa; // [rsp+50h] [rbp-10h]

  heapa = heap;
  othera = other;
  if ( heap->roots_length <= other->roots_length )
    roots_length = othera->roots_length;
  else
    roots_length = heapa->roots_length;
  max = roots_length + 1;
  new_roots = (BinomialTree **)malloc(8LL * (roots_length + 1));
  if ( !new_roots )
    return 0;
  new_roots_length = 0;
  carry = 0LL;
  for ( i = 0; i < max; ++i )
  {
    num_vals = 0;
    if ( i < heapa->roots_length && heapa->roots[i] )
    {
      vals[0] = heapa->roots[i];
      num_vals = 1;
    }
    if ( i < othera->roots_length && othera->roots[i] )
      vals[num_vals++] = othera->roots[i];
    if ( carry )
      vals[num_vals++] = carry;
    if ( (num_vals & 1) != 0 )
    {
      new_roots[i] = vals[num_vals - 1];
      binomial_tree_ref(new_roots[i]);
      new_roots_length = i + 1;
    }
    else
    {
      new_roots[i] = 0LL;
    }
    if ( (num_vals & 2) != 0 )
    {
      new_carry = binomial_tree_merge(heapa, vals[0], vals[1]);
      if ( !new_carry )
      {
        binomial_heap_merge_undo(new_roots, i);
        binomial_tree_unref(carry);
        return 0;
      }
    }
    else
    {
      new_carry = 0LL;
    }
    binomial_tree_unref(carry);
    carry = new_carry;
    binomial_tree_ref(new_carry);
  }
  for ( ia = 0; ia < heapa->roots_length; ++ia )
  {
    if ( heapa->roots[ia] )
      binomial_tree_unref(heapa->roots[ia]);
  }
  free(heapa->roots);
  heapa->roots = new_roots;
  heapa->roots_length = new_roots_length;
  return 1;
}