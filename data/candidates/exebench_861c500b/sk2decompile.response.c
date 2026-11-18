char *fix(char *dest, char *src) {
  int i = 0, j = 0;
  while (src[i]) {
    if (src[i] == '\b') {
      j--;
      if (j < 0) j = 0;
    } else
      dest[j++] = src[i];
    i++;
  }
  dest[j] = 0;
  return dest;
}