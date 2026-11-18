int mustache_buffer_insert(MUSTACHE_BUFFER *buf, off_t off, const void *data, size_t n)
{
  if (buf->alloc < buf->n + n) {
    size_t new_alloc = (buf->n + n) * 2;
    void *new_data = realloc(buf->data, new_alloc);
    if (!new_data) return -1;
    buf->data = new_data;
    buf->alloc = new_alloc;
  }

  if (buf->n > off) {
    memmove(buf->data + off + n, buf->data + off, buf->n - off);
  }

  memcpy(buf->data + off, data, n);
  buf->n += n;

  return 0;
}