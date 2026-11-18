char *_hamming_distance_calculate_bits(const char *a, const char *b) {
  int min_length, a_length, b_length;
  char *bits;
  a_length = strlen(a);
  b_length = strlen(b);
  if (a_length < b_length) {
    min_length = a_length;
  } else {
    min_length = b_length;
  }
  bits = malloc(min_length + 1);
  if (bits == NULL) {
    return NULL;
  }
  for (int i = 0; i < min_length; i++) {
    char bit = '1';
    if (a[i] == b[i]) {
      bit = '0';
    }
    bits[i] = bit;
  }
  bits[min_length] = '\0';
  return bits;
}