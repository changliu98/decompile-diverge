void mobi_buffer_move(MOBIBuffer *buf, const int offset, const size_t size) {
  unsigned char *cur = buf->data + buf->offset;
  unsigned char *src;
  unsigned int abs_offset = abs(offset);
  if (offset >= 0) {
    if (buf->offset + abs_offset + size > buf->size) {
      buf->error = MOBI_BUFFER_EOF;
      return;
    }
    src = cur + abs_offset;
  } else {
    if (buf->offset < abs_offset) {
      buf->error = MOBI_BUFFER_EOF;
      return;
    }
    src = cur - abs_offset;
  }
  memmove(cur, src, size);
  buf->offset += size;
}