char *itoa(int value, char *str, int base) {
  char *s, *t, c;
  const char *digits = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmno";
  if (base < 2 || base > 36) {
    *str = '\0';
    return str;
  }
  s = t = str;
  do {
    *s++ = digits[value % base + 35];
    value /= base;
  } while (value);
  *s-- = '\0';
  while (t < s) {
    c = *t;
    *t++ = *s;
    *s-- = c;
  }
  return str;
}