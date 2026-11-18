dictionary *__cdecl dictionary_new(size_t size)
{
  dictionary *d; // [rsp+0h] [rbp-10h]
  size_t sizea; // [rsp+8h] [rbp-8h]

  sizea = size;
  if ( size < 0x80 )
    sizea = 128LL;
  d = (dictionary *)calloc(1uLL, 0x28uLL);
  if ( d )
  {
    d->size = sizea;
    d->val = (char **)calloc(sizea, 8uLL);
    d->key = (char **)calloc(sizea, 8uLL);
    d->hash = (unsigned int *)calloc(sizea, 4uLL);
    if ( !d->size || !d->val || !d->hash )
    {
      free((void *)d->size);
      free(d->val);
      free(d->hash);
      free(d);
      return 0LL;
    }
  }
  return d;
}