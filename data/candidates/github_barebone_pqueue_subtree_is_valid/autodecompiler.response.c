int heap_is_valid(heap_t *heap)
{
    assert__bench(heap != NULL);

    return subtree_is_valid(heap, 0);
}