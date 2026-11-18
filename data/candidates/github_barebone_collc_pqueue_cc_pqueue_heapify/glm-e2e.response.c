void cc_pqueue_heapify(struct pqueue* pq, long long idx) {
    if (pq->size <= 1) {
        return;
    }

    long long left = 2 * idx + 1;
    long long right = 2 * idx + 2;
    long long largest = idx;

    void* left_val = pq->data[left];
    void* right_val = pq->data[right];
    void* current_val = pq->data[idx];

    if (left < pq->size && pq->cmp(current_val, left_val) < 0) {
        current_val = left_val;
        largest = left;
    }

    if (right < pq->size && pq->cmp(current_val, right_val) < 0) {
        current_val = right_val;
        largest = right;
    }

    if (largest != idx) {
        void* tmp = pq->data[idx];
        pq->data[idx] = pq->data[largest];
        pq->data[largest] = tmp;
        
        cc_pqueue_heapify(pq, largest);
    }
}