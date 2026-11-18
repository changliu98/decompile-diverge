struct _dictionary *dictionary_new(unsigned long size)
{
  struct _dictionary *d = ((void *)0);
  if (size < 128)
    size = 128;
  d = (struct _dictionary *)calloc(1, sizeof(*d));
  if (d != ((void *)0)) {
    d->size = size;
    d->val = (void **)calloc(size, sizeof(*d->val));
    d->key = (void **)calloc(size, sizeof(*d->key));
    d->hash = (unsigned int *)calloc(size, sizeof(*d->hash));
    if (d->size == 0 || d->val == ((void *)0) || d->hash == ((void *)0)) {
      free(d->size);
      free(d->val);
      free(d->hash);
      free(d);
      return ((void *)0);
    }
  }
  return d;
}