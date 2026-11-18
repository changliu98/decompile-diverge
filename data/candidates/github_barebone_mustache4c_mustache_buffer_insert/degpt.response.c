int mustache_buffer_insert(MUSTACHE_BUFFER *buf,off_t off,void *data,size_t n)

{
  size_t __size;
  uint8_t *puVar1;
  uint8_t *new_data;
  size_t new_alloc;
  size_t n_local;
  void *data_local;
  off_t off_local;
  MUSTACHE_BUFFER *buf_local;
  
  if (buf->alloc < buf->n + n) {
    __size = (buf->n + n) * 2;
    puVar1 = realloc(buf->data,__size);
    if (puVar1 == (uint8_t *)0x0) {
      return -1;
    }
    buf->data = puVar1;
    buf->alloc = __size;
  }
  if ((ulong)off < buf->n) {
    memmove(buf->data + n + off,buf->data + off,buf->n - off);
  }
  memcpy(buf->data + off,data,n);
  buf->n = n + buf->n;
  return 0;
}