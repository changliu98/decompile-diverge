int sortedarray_insert(sortedarray *sa, sortedarray_data data) {
  unsigned int i, j, k;
  int cmp;
  sortedarray_data *new_data;
  if (sa == NULL) return 0;
  i = 0;
  j = 0;
  k = sa->size > 1 ? sa->size : 0;
  while (i != k) {
    j = (i + k) / 2;
    cmp = sa->compare(data, sa->data[j]);
    if (cmp < 0)
      k = j;
    else if (cmp > 0)
      i = j + 1;
    else
      break;
  }
  if (sa->size && sa->compare(data, sa->data[j]) > 0) j++;
  if (sa->size + 1 > sa->alloc) {
    unsigned int new_alloc = sa->alloc * 2;
    new_data = realloc(sa->data, new_alloc * sizeof(sortedarray_data));
    if (new_data == NULL) return 0;
    sa->data = new_data;
    sa->alloc = new_alloc;
  }
  memmove(sa->data + j + 1, sa->data + j,
          (sa->size - j) * sizeof(sortedarray_data));
  sa->data[j] = data;
  sa->size++;
  return 1;
}