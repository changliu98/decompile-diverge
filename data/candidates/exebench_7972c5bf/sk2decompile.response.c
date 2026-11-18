void tagcpy(char *dest, char *src, int len) {
  char *s, *e;
  s = src;
  e = src + len - 1;
  if (*e && !(*(e - 1))) e--;
  while (s <= e) {
    if (*s == ' ')
      s++;
    else if (*e == 0 || *e == ' ')
      e--;
    else
      break;
  }
  while (*s && s <= e) *dest++ = *s++;
  *dest = 0;
}