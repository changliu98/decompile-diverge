char *_rotate(char *str, int n) {
  int i, len;
  char *ret;
  len = strlen(str);
  ret = malloc(len + 1);
  for (i = 0; i < len; i++) {
    ret[i] = str[(i + n) % len];
  }
  ret[len] = '\0';
  return ret;
}