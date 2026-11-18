int is_uletter(char c) {
  int ret = 0;
  if (c >= 'A' && c <= 'Z') {
    ret = 1;
  }
  return ret;
}