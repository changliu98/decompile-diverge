struct hash *dictionary_new(size_t size)
{
 struct hash *h;

 if (size < 128)
  size = 128;

 h = calloc(1, sizeof(struct hash));
 if (h) {
  h->size = size;
  h->keys = calloc(size, sizeof(char *));
  h->values = calloc(size, sizeof(void *));
  h->used = calloc(size, sizeof(int));

  if (!h->size || !h->keys || !h->used) {
   free(h->size);
   free(h->keys);
   free(h->used);
   free(h);
   h = NULL;
  }
 }

 return h;
}