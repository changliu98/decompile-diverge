void check_int(int *start, int *end, char *result) {
  if (end - start == 1) {
    *result = 't';
  } else {
    *result = 'f';
  }
}