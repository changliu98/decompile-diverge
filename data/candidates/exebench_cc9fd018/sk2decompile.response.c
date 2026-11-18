int safe_calloc_check_add(unsigned int nmemb, unsigned int size,
                          unsigned int *result) {
  unsigned int tmp;
  unsigned int *res = result ? result : &tmp;
  *res = nmemb + size;
  return nmemb <= tmp;
}