int mustache_buffer_insert(struct MUSTACHE_BUFFER *buf, long off, void *data, unsigned long n)
{
  if (buf->n + n > buf->alloc) {
    unsigned long new_alloc = (buf->n + n) * 2;
    char *new_data = realloc(buf->data, new_alloc);
    if (new_data == ((void *)0)) {
      return -1;
    }
    buf->data = new_data;
    buf->alloc = new_alloc;
  }
  if (off < buf->n) {
    memmove(buf->data + off + n, buf->data + off, buf->n - off);
  }
  memcpy(buf->data + off, data, n);
  buf->n += n;
  return 0;
}