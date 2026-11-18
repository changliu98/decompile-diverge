dictionary * dictionary_new(size_t size)
{
 dictionary * d ;


 if (size<128) size=128 ;

 if (!(d = calloc(1, sizeof(*d)))) {
  return NULL ;
 }
 d->size = size ;
 d->val = calloc(size, sizeof(char *));
 d->key = calloc(size, sizeof(char *));
 d->hash = calloc(size, sizeof(unsigned));
 if (!d->size || !d->val || !d->hash) {
  free(d->size);
  free(d->val);
  free(d->hash);
  free(d);
  return NULL ;
 }
 return d ;
}