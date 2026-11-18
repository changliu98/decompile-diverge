char *jstrescapecpy(char *dest, const char *src) {
  int i = 0, j = 0;
  int c;
  if (src == NULL) {
    dest[0] = '\0';
    return dest;
  }
  while (src[i] != '\0') {
    c = src[i];
    if (c == '%') {
      dest[j++] = '_';
      i++;
    } else if (c == '\'') {
      dest[j++] = '\\';
      dest[j++] = src[i++];
    } else if (c == '\\') {
      dest[j++] = '\\';
      dest[j++] = src[i++];
    } else {
      dest[j++] = src[i++];
    }
  }
  dest[j] = '\0';
  return dest;
}