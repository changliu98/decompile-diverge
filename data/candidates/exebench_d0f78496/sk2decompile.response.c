char *read_int(char *s, int n, int *i) {
  int j = 0;
  while (--n >= 0 && *s >= '0' && *s <= '9') {
    j = j * 10 + (*s - '0');
    s++;
  }
  *i = j;
  return s;
}