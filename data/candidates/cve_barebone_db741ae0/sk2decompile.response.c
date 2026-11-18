static int burl_normalize_2F_to_slash_fix(buffer *b, int start, int end) {
  char *data = b->ptr;
  int len = buffer_string_length(b);
  int end_ = (start < 0) ? len : start;
  int i = end;
  int j;
  for (j = end; j < end_; j++, i++) {
    data[i] = data[j];
    if (data[j] == '%' && data[j + 1] == '2' && data[j + 2] == 'F') {
      data[i] = '/';
      j += 2;
    }
  }
  if (start >= 0) {
    memmove(data + i, data + start, len - start);
    i += len - start;
  }
  buffer_string_set_length(b, i);
  return start;
}