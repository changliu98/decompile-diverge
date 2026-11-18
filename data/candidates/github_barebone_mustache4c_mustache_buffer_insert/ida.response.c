int __cdecl mustache_buffer_insert(MUSTACHE_BUFFER *buf, off_t off, const void *data, size_t n)
{
  uint8_t *new_data; // [rsp+8h] [rbp-38h]
  size_t new_alloc; // [rsp+10h] [rbp-30h]

  if ( n + buf->n > buf->alloc )
  {
    new_alloc = 2 * (n + buf->n);
    new_data = (uint8_t *)realloc(buf->data, new_alloc);
    if ( !new_data )
      return -1;
    buf->data = new_data;
    buf->alloc = new_alloc;
  }
  if ( off < buf->n )
    memmove(&buf->data[off + n], &buf->data[off], buf->n - off);
  memcpy(&buf->data[off], data, n);
  buf->n += n;
  return 0;
}