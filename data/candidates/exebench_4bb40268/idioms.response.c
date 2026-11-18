void check_int(int *a, int *b, char *out) {
  *out = a - b == 4 ? 't' : 'f';
}