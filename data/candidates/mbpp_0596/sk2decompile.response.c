size_t _talloc_size_of_array(void **array, size_t n) {
  size_t size = 0;
  size_t i;
  for (i = 0; i < n; i++) {
    size += sizeof(void *);
  }
  return size;
}