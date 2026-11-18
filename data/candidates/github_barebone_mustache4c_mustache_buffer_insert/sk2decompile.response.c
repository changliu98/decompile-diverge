int mustache_buffer_insert(mustache_buffer_t *buf, size_t pos, const char *str,
                           size_t len) {
  if (buf->capacity < len + buf->length) {
    size_t new_capacity = (len + buf->length) * 2;
    char *new_buf = realloc(buf->buf, new_capacity);
    if (!new_buf) return -1;
    buf->buf = new_buf;
    buf->capacity = new_capacity;
  }
  if (pos < buf->length)
    memmove(buf->buf + pos + len, buf->buf + pos, buf->length - pos);
  memcpy(buf->buf + pos, str, len);
  buf->length += len;
  return 0;
}