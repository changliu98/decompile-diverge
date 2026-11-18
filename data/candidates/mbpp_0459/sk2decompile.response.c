char *_pico_strtolower(const char *str) {
  size_t len = strlen(str);
  char *ret = malloc(len + 1);
  if (ret == NULL) return NULL;
  size_t i, j = 0;
  for (i = 0; i < len; i++) {
    if (!isupper((unsigned char)str[i])) {
      ret[j++] = str[i];
    }
  }
  ret[j] = '\0';
  return ret;
}