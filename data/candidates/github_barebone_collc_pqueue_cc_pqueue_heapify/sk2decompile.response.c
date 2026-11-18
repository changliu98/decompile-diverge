static void cc_pqueue_heapify(CC_PQueue *self, unsigned i) {
  if (self->size <= 1) return;
  unsigned l = i * 2 + 1;
  unsigned r = i * 2 + 2;
  unsigned smallest = i;
  void *a = self->nodes[i];
  void *b = self->nodes[l];
  void *c = self->nodes[r];
  if (l < self->size && self->cmp(a, b) < 0) {
    a = b;
    smallest = l;
  }
  if (r < self->size && self->cmp(a, c) < 0) smallest = r;
  if (smallest != i) {
    void *tmp = self->nodes[i];
    self->nodes[i] = self->nodes[smallest];
    self->nodes[smallest] = tmp;
    cc_pqueue_heapify(self, smallest);
  }
}