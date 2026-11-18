int burl_normalize_2F_to_slash_fix(struct buffer *buf, int end, int start)
{
  int i; int j; int len;
  char *ptr;
  ptr = buf->ptr;
  len = buffer_len(buf);
  if (end < 0)
    end = len;
  for (i = start, j = start; i < end; i++, j++) {
    ptr[j] = ptr[i];
    if (ptr[i] == '%' && ptr[i + 1] == '2' && ptr[i + 2] == 'F') {
      ptr[j] = '/';
      i += 2;
    }
  }
  if (end >= 0) {
    buffer_append(&ptr[j], &ptr[end], len - end);
    j += len - end;
  }
  buffer_setlen(buf, j);
  return (end);
}