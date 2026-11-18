int pqueue_insert(struct PQueue *pq, void *item) {
    if (pq == NULL) {
        return 1;
    }

    if (pq->size >= pq->capacity) {
        size_t new_capacity = pq->capacity + pq->grow_by;
        void **new_data = realloc(pq->data, new_capacity * sizeof(void *));
        
        if (new_data == NULL) {
            return 1;
        }
        
        pq->data = new_data;
        pq->capacity = new_capacity;
    }

    size_t index = pq->size;
    pq->size++;
    pq->data[index] = item;
    
    bubble_up(pq, index);
    
    return 0;
}