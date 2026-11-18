char *itoa(int value, char *string, int base) {
  char *s, *t, c;
  int sign;
  if (base < 2 || base > 36) {
    *string = '\0';
    return string;
  }
  s = string;
  if ((sign = value) < 0) {
    *s++ = '-';
  }
  t = s;
  do {
    *s++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[sign % base + 35];
  } while (sign /= base);
  *s-- = '\0';
  while (t < s) {
    c = *t;
    *t++ = *s;
    *s-- = c;
  }
  return string;
}