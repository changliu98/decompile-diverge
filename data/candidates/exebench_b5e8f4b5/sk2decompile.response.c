static const char *convert_set_base(const char *str, int *base) {
  const char *p = str;
  *base = 10;
  if (str && *str == '0') {
    p = str + 1;
    if (*p == 'x' || *p == 'X') {
      *base = 16;
      p++;
    }
  }
  return p;
}