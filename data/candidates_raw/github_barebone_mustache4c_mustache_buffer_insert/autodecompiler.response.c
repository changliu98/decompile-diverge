int cstr_insert(cstr *s, size_t pos, char *src, size_t len) {
  int ret;
  if(s->size + len > s->alloc) {
    size_t new_alloc = (s->size + len) * 2;
    char *new_str = realloc(s->str, new_alloc);
    if(new_str == NULL) {
      ret = -1;
      goto exit;
    }
    s->str = new_str;
    s->alloc = new_alloc;
  }
  if(pos < s->size) {
    memmove(s->str + pos + len, s->str + pos, s->size - pos);
  }
  memcpy(s->str + pos, src, len);
  s->size += len;
  ret = 0;
exit:
  return ret;
}