int safe_calloc_check_mul(unsigned int nmemb, unsigned int size,
                          unsigned int *result) {
  unsigned int dummy;
  unsigned int *p = result ? result : &dummy;
  *p = nmemb * size;
  if (nmemb * size / size != nmemb) return 0;
  return 1;
}