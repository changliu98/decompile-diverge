int __cdecl dictionary_grow(dictionary *d)
{
  unsigned int *new_hash; // [rsp+8h] [rbp-28h]
  char **new_key; // [rsp+10h] [rbp-20h]
  char **new_val; // [rsp+18h] [rbp-18h]

  new_val = (char **)calloc(2 * d->size, 8uLL);
  new_key = (char **)calloc(2 * d->size, 8uLL);
  new_hash = (unsigned int *)calloc(2 * d->size, 4uLL);
  if ( new_val && new_key && new_hash )
  {
    memcpy(new_val, d->val, 8 * d->size);
    memcpy(new_key, d->key, 8 * d->size);
    memcpy(new_hash, d->hash, 4 * d->size);
    free(d->val);
    free(d->key);
    free(d->hash);
    d->size *= 2LL;
    d->val = new_val;
    d->key = new_key;
    d->hash = new_hash;
    return 0;
  }
  else
  {
    if ( new_val )
      free(new_val);
    if ( new_key )
      free(new_key);
    if ( new_hash )
      free(new_hash);
    return -1;
  }
}