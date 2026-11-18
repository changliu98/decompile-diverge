void cc_pqueue_heapify(CC_PQueue *pq, size_t index)
{
    if (pq->size < 2)
        return;

    size_t left = (2 * index) + 1;
    size_t right = (2 * index) + 2;

    size_t smallest = index;

    if (left < pq->size && pq->cmp(pq->buffer[smallest], pq->buffer[left]) < 0)
        smallest = left;

    if (right < pq->size && pq->cmp(pq->buffer[smallest], pq->buffer[right]) < 0)
        smallest = right;

    if (smallest != index) {
        void *tmp = pq->buffer[index];
        pq->buffer[index] = pq->buffer[smallest];
        pq->buffer[smallest] = tmp;
        cc_pqueue_heapify(pq, smallest);
    }
}