void _itoa(int value, int base, char *result) {
  char tmp[32];
  int i = 0;
  int j = 0;
  while (value > 0) {
    tmp[i++] = '0' + value % base;
    value /= base;
  }
  i = 0;
  while (i < j) {
    result[i++] = tmp[--j];
  }
  result[i] = '\0';
}