int dictionary_grow(dictionary *d)

{
  char **__dest;
  char **__dest_00;
  uint *__dest_01;
  uint *new_hash;
  char **new_key;
  char **new_val;
  dictionary *d_local;
  int local_c;
  
  __dest = calloc(d->size << 1,8);
  __dest_00 = calloc(d->size << 1,8);
  __dest_01 = calloc(d->size << 1,4);
  if (((__dest == (char **)0x0) || (__dest_00 == (char **)0x0)) || (__dest_01 == (uint *)0x0)) {
    if (__dest != (char **)0x0) {
      free(__dest);
    }
    if (__dest_00 != (char **)0x0) {
      free(__dest_00);
    }
    if (__dest_01 != (uint *)0x0) {
      free(__dest_01);
    }
    local_c = -1;
  }
  else {
    memcpy(__dest,d->val,d->size << 3);
    memcpy(__dest_00,d->key,d->size << 3);
    memcpy(__dest_01,d->hash,d->size << 2);
    free(d->val);
    free(d->key);
    free(d->hash);
    d->size = d->size << 1;
    d->val = __dest;
    d->key = __dest_00;
    d->hash = __dest_01;
    local_c = 0;
  }
  return local_c;
}