static int try_enlarge(buffer_t *buf, unsigned int len) {
  unsigned int new_size = buf->size;
  char *new_data;
  while (new_size < buf->len + len) {
    new_size *= 2;
  }
  new_data = realloc(buf->data, new_size);
  if (new_data == NULL) {
    return -1;
  }
  buf->data = new_data;
  buf->size = new_size;
  return 0;
}