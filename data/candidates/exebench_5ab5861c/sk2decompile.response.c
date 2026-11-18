char *itoa(long value, char *str, int base) {
  const char num[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *ptr, *ptr1, tmp;
  char *str1 = str;
  if (str == NULL || base < 2 || base > 36) return str;
  if (base != 10 && value < 0) return str;
  if (value == 0) {
    *str++ = '0';
    *str = '\0';
    return str;
  }
  if (base == 10 && value < 0) {
    *str++ = '-';
    value = -value;
  }
  ptr = str;
  while (value != 0) {
    *ptr++ = num[value % base];
    value /= base;
  }
  *ptr = '\0';
  ptr1 = ptr - 1;
  while (str1 < ptr1) {
    tmp = *str1;
    *str1 = *ptr1;
    *ptr1 = tmp;
    str1++;
    ptr1--;
  }
  return str;
}