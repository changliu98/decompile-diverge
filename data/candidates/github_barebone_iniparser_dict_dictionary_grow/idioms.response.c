int dictionary_grow(struct _dictionary *d)
{
  void **new_val = ((void *)0);
  void **new_key = ((void *)0);
  unsigned int *new_hash = ((void *)0);
  new_val = (void **)dictionary_malloc(d->size * 2, sizeof(void *));
  new_key = (void **)dictionary_malloc(d->size * 2, sizeof(void *));
  new_hash = (unsigned int *)dictionary_malloc(d->size * 2, sizeof(unsigned int));
  if (new_val == ((void *)0) || new_key == ((void *)0) || new_hash == ((void *)0))
  {
    if (new_val != ((void *)0))
      dictionary_free(new_val);
    if (new_key != ((void *)0))
      dictionary_free(new_key);
    if (new_hash != ((void *)0))
      dictionary_free(new_hash);
    return -1;
  }
  dictionary_memcpy(new_val, d->val, d->size * sizeof(void *));
  dictionary_memcpy(new_key, d->key, d->size * sizeof(void *));
  dictionary_memcpy(new_hash, d->hash, d->size * sizeof(unsigned int));
  dictionary_free(d->val);
  dictionary_free(d->key);
  dictionary_free(d->hash);
  d->size *= 2;
  d->val = new_val;
  d->key = new_key;
  d->hash = new_hash;
  return 0;
}