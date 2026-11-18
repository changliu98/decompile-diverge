char *itoa(int value, char *str, int base)
{
  char *p; char *low; char tmp;
  if (base < 2 || base > 36)
    return str;
  for (p = str, low = str; ; ) {
    *p++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[value % base + 35];
    if ((value /= base) == 0)
      break;
  }
  *p-- = '\0';
  while (low < p) {
    tmp = *low;
    *low++ = *p;
    *p-- = tmp;
  }
  return str;
}