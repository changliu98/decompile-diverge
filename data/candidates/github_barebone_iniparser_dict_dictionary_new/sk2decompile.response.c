dictionary *dictionary_new(int size) {
  dictionary *d;
  if (size < 128) size = 128;
  d = calloc(1, sizeof(dictionary));
  if (d) {
    d->size = size;
    d->key = calloc(size, sizeof(char *));
    d->val = calloc(size, sizeof(char *));
    d->hash = calloc(size, sizeof(int));
    if (!d->size || !d->key || !d->hash) {
      free(d->size);
      free(d->key);
      free(d->hash);
      free(d);
      d = NULL;
    }
  }
  return d;
}