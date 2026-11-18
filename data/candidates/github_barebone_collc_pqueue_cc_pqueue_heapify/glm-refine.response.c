void __cdecl cc_pqueue_heapify(CC_PQueue *pq, size_t index)
{
    size_t size = pq->size;
    if (size <= 1)
        return;

    void **buffer = pq->buffer;
    size_t left_idx = 2 * index + 1;
    size_t right_idx = 2 * index + 2;
    size_t largest_idx = index;

    void *largest = buffer[index];

    // Check if the left child exists and is greater than the current largest
    if (left_idx < size && pq->cmp(largest, buffer[left_idx]) < 0)
    {
        largest = buffer[left_idx];
        largest_idx = left_idx;
    }

    // Check if the right child exists and is greater than the current largest
    if (right_idx < size && pq->cmp(largest, buffer[right_idx]) < 0)
    {
        largest_idx = right_idx;
    }

    // If the largest element is not the original index, swap and recurse
    if (largest_idx != index)
    {
        void *swap_tmp = buffer[index];
        buffer[index] = buffer[largest_idx];
        buffer[largest_idx] = swap_tmp;
        
        cc_pqueue_heapify(pq, largest_idx);
    }
}