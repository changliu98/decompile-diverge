BinomialHeapValue __cdecl binomial_heap_pop(BinomialHeap *heap)
{
    unsigned int least_index;
    unsigned int i;
    BinomialHeapValue result;
    BinomialHeap fake_heap;
    BinomialTree *least_tree;

    // Return 0 if the heap is empty
    if (!heap->num_values)
        return 0LL;

    // Find the root tree with the minimum value
    least_index = -1;
    for (i = 0; i < heap->roots_length; ++i)
    {
        if (heap->roots[i] && 
            (least_index == -1 || binomial_heap_cmp(heap, heap->roots[i]->value, heap->roots[least_index]->value) < 0))
        {
            least_index = i;
        }
    }

    // Extract the minimum tree and clear its slot in the root list
    least_tree = heap->roots[least_index];
    heap->roots[least_index] = 0LL;

    // Initialize a temporary heap from the extracted tree's subtrees
    fake_heap.heap_type = heap->heap_type;
    fake_heap.compare_func = heap->compare_func;
    fake_heap.roots = least_tree->subtrees;
    fake_heap.roots_length = least_tree->order;

    // Merge the subtrees back into the original heap
    if (binomial_heap_merge(heap, &fake_heap))
    {
        // Success: clean up, decrement count, and return the minimum value
        result = least_tree->value;
        binomial_tree_unref(least_tree);
        --heap->num_values;
        return result;
    }
    else
    {
        // Merge failed: restore the original tree and return 0
        heap->roots[least_index] = least_tree;
        return 0LL;
    }
}