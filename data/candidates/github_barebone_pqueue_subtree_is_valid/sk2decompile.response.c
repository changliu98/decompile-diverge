static int subtree_is_valid(heap_t *h, int i) {
  if (2 * i < h->size) {
    if (h->cmp(h->data[i], h->data[2 * i]) != 0) return 0;
    if (!subtree_is_valid(h, 2 * i)) return 0;
  }
  if (2 * i + 1 < h->size) {
    if (h->cmp(h->data[i], h->data[2 * i + 1]) != 0) return 0;
    if (!subtree_is_valid(h, 2 * i + 1)) return 0;
  }
  return 1;
}