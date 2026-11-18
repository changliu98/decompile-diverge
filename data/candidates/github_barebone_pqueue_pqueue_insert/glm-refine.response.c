int __cdecl pqueue_insert(pqueue_t *q, void *d)
{
    void **new_d;

    if (!q)
        return 1;

    // If the queue is full, expand its capacity
    if (q->size >= q->avail)
    {
        size_t newsize = q->size + q->step;
        new_d = (void **)realloc(q->d, 8 * newsize); // 8 * newsize (sizeof(void*) on x64)
        
        if (!new_d)
            return 1;
            
        q->d = new_d;
        q->avail = newsize;
    }

    // Insert the new element at the end and increment the size
    q->d[q->size] = d;
    q->size++;
    
    // Restore the heap property
    bubble_up(q, q->size - 1);

    return 0;
}