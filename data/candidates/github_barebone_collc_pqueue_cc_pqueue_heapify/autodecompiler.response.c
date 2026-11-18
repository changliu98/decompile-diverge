static void cc_pqueue_heapify(CC_PQueue *q, size_t i)
{
    if (q->size < 2)
        return;

    size_t l = ((i << 1) + 1);
    size_t r = ((i << 1) + 2);
    size_t p = i;

    void *left = q->buffer[l];
    void *right = q->buffer[r];
    void *data = q->buffer[i];

    if (l < q->size && q->cmp(data, left) < 0) {
        data = left;
        i = l;
    }

    if (r < q->size && q->cmp(data, right) < 0) {
        data = right;
        i = r;
    }

    if (i != p) {
        void *tmp = q->buffer[p];
        q->buffer[p] = q->buffer[i];
        q->buffer[i] = tmp;

        cc_pqueue_heapify(q, i);
    }
}