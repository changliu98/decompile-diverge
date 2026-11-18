int utoa(char *str, unsigned int value, int base) {
  char buf[128];
  char *end = buf + sizeof(buf) - 1;
  char *p = buf + sizeof(buf) - 1;
  char *s = str;
  char hex_lower[17];
  char hex_upper[17];
  int divisor;
  char *hex;
  int len;
  strcpy(hex_lower, "0123456789abcdef");
  strcpy(hex_upper, "0123456789ABCDEF");
  switch (base) {
    case 'd':
    case 'i':
    case 'u':
      divisor = 10;
      break;
    case 'o':
      divisor = 8;
      break;
    case 'x':
      divisor = 16;
      hex = hex_lower;
      break;
    case 'X':
      divisor = 16;
      hex = hex_upper;
      break;
    default:
      return -1;
  }
  do {
    switch (divisor) {
      case 8:
        *p-- = (value & 0x07) + '0';
        break;
      case 10:
        *p-- = (value % 10) + '0';
        break;
      case 16:
        *p-- = hex[value & 0x0f];
        break;
    }
    value /= divisor;
  } while (value);
  p++;
  while (p < end) {
    *s++ = *p;
    p++;
  }
  *s = '\0';
  len = s - str;
  return len;
}