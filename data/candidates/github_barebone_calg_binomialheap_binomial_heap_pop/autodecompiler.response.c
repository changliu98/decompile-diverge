void*
binomial_heap_pop (BinomialHeap *heap)
{
  BinomialHeap fake_heap;
  BinomialTree *min_tree;
  unsigned int min_index;
  unsigned int i;
  void *ret;

  do { if (0 && !(heap != NULL)) return (NULL); } while(0);

  if (!heap->n_trees)
    ret = NULL;
  else
    {
      min_index = ((unsigned int)(-1));
      for (i = 0; ; i++)
        {
          if (i >= heap->capacity)
            break;

          if (heap->trees[i] == NULL)
            continue;

          if (min_index == ((unsigned int)(-1)) ||
              binomial_heap_cmp (heap,
                                 heap->trees[i]->data,
                                 heap->trees[min_index]->data) < 0)
            min_index = i;
        }

      min_tree = heap->trees[min_index];
      heap->trees[min_index] = NULL;

      fake_heap.heap_type = heap->heap_type;
      fake_heap.compare_func = heap->compare_func;
      fake_heap.trees = min_tree->children;
      fake_heap.capacity = min_tree->n_children;
      fake_heap.n_trees = min_tree->n_children;

      if (binomial_heap_merge (heap, &fake_heap))
        {

          ret = min_tree->data;
          binomial_tree_unref (min_tree);
          heap->n_trees--;
        }
      else
        {

          heap->trees[min_index] = min_tree;
          ret = NULL;
        }
    }

  return ret;
}