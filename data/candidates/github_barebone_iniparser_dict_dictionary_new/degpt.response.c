dictionary * dictionary_new(size_t size)

{
  char **ppcVar1;
  uint *puVar2;
  dictionary *d;
  size_t size_local;
  
  size_local = size;
  if (size < 0x80) {
    size_local = 0x80;
  }
  d = calloc(1,0x28);
  if (d != (dictionary *)0x0) {
    d->size = size_local;
    ppcVar1 = calloc(size_local,8);
    d->val = ppcVar1;
    ppcVar1 = calloc(size_local,8);
    d->key = ppcVar1;
    puVar2 = calloc(size_local,4);
    d->hash = puVar2;
    if (((d->size == 0) || (d->val == (char **)0x0)) || (d->hash == (uint *)0x0)) {
      free((void *)d->size);
      free(d->val);
      free(d->hash);
      free(d);
      d = (dictionary *)0x0;
    }
  }
  return d;
}