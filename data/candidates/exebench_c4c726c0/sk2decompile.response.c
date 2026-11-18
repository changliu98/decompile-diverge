void check_long(long *a, long *b, char *c) {
  char d = 'f';
  if (b - a == 1) d = 't';
  *c = d;
}