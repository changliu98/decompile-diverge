unsigned int itoa(unsigned int value, char *str, unsigned int base) {
  const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char tmp[32];
  unsigned int i, j;
  if (base < 2 || base > 36) return 0;
  if (value == 0) {
    str[0] = '0';
    return 1;
  }
  j = 0;
  while (value > 0) {
    i = value % base;
    value /= base;
    tmp[j] = digits[i];
    j++;
  }
  for (i = 0; i < j; i++) str[i] = tmp[j - 1 - i];
  return i;
}