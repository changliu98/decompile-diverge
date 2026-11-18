int pqueue_insert(pqueue_t *pq, void *item) {
  if (pq == NULL) return 1;
  if (pq->size >= pq->capacity) {
    int new_capacity = pq->size + pq->growth_factor;
    void **new_items = realloc(pq->items, new_capacity * sizeof(void *));
    if (new_items == NULL) return 1;
    pq->items = new_items;
    pq->capacity = new_capacity;
  }
  int index = pq->size++;
  pq->items[index] = item;
  bubble_up(pq, index);
  return 0;
}