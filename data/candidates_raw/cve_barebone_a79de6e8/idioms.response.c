void mobi_buffer_seek(struct MOBIBuffer *buf, int offset, long len)
{
  offset = mobi_buffer_round(offset);
  unsigned char *data = &buf->data[buf->offset];
  if (offset >= 0) {
    if (buf->offset + len + offset > buf->maxlen) {
      buf->error = MOBI_BUFFER_END;
      return;
    }
    data += offset;
  } else {
    if (buf->offset < offset) {
      buf->error = MOBI_BUFFER_END;
      return;
    }
    data -= offset;
  }
  memmove(&buf->data[buf->offset], data, len);
  buf->offset += len;
}