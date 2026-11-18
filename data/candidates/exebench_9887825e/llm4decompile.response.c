int _safe_calloc_check_mul(size_t a, size_t b, size_t *res) {
  if (!res) {
    size_t tmp;
    res = &tmp;
  }

  *res = a * b;

  if (*res / b != a) {
    return 0;
  }

  return 1;
}