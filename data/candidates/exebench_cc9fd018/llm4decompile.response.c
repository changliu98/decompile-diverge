int _safe_calloc_check_add(size_t a, size_t b, size_t *res) {
  size_t tmp;
  if (res == NULL) {
    res = &tmp;
  }
  *res = a + b;
  if (*res < a) {
    return 1;
  }
  return 0;
}