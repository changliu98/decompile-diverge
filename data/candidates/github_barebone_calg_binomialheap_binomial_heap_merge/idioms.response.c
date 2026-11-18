int binomial_heap_merge(struct BinomialHeap *heap, struct BinomialHeap *other)
{
  struct BinomialTree *vals[2];
  struct BinomialTree *new_carry = ((void *)0);
  struct BinomialTree *carry = ((void *)0);
  struct BinomialTree **new_roots = ((void *)0);
  struct BinomialHeap *heap1 = ((void *)0);
  struct BinomialHeap *other1 = ((void *)0);
  unsigned int i = 0;
  unsigned int num_vals = 0;
  unsigned int max = 0;
  unsigned int new_roots_length = 0;
  heap1 = heap;
  other1 = other;
  if (heap->roots_length > other->roots_length)
  {
    max = heap->roots_length;
  }
  else
  {
    max = other->roots_length;
  }
  max++;
  new_roots = (struct BinomialTree **)BinomialHeapMemAlloc(max * sizeof(struct BinomialTree *));
  if (new_roots == ((void *)0))
  {
    return 0;
  }
  new_roots_length = 0;
  for (i = 0; i < max; i++)
  {
    num_vals = 0;
    if (i < heap1->roots_length && heap1->roots[i] != ((void *)0))
    {
      vals[num_vals] = heap1->roots[i];
      num_vals++;
    }
    if (i < other1->roots_length && other1->roots[i] != ((void *)0))
    {
      vals[num_vals] = other1->roots[i];
      num_vals++;
    }
    if (carry != ((void *)0))
    {
      vals[num_vals] = carry;
      num_vals++;
    }
    if (num_vals % 2 == 1)
    {
      new_roots[i] = vals[num_vals - 1];
      BinomialTreeMark(new_roots[i]);
      new_roots_length = i + 1;
    }
    else
    {
      new_roots[i] = ((void *)0);
    }
    if (num_vals % 2 == 0)
    {
      new_carry = BinomialTreeMerge(heap1, vals[0], vals[1]);
      if (new_carry == ((void *)0))
      {
        BinomialTreeFree(new_roots, i);
        BinomialTreeFree(carry);
        return 0;
      }
    }
    else
    {
      new_carry = ((void *)0);
    }
    BinomialTreeFree(carry);
    carry = new_carry;
    BinomialTreeMark(carry);
  }
  for (i = 0; i < heap1->roots_length; i++)
  {
    if (heap1->roots[i] != ((void *)0))
    {
      BinomialTreeFree(heap1->roots[i]);
    }
  }
  BinomialHeapFreeRoots(heap1->roots);
  heap1->roots = new_roots;
  heap1->roots_length = new_roots_length;
  return 1;
}