char *_pbcC_upper_first_lower_rest(const char *str) {
  size_t len = strlen(str);
  char *ret = malloc(len + 1);
  if (ret == NULL) return NULL;
  if (len > 0) {
    ret[0] = toupper(str[0]);
    for (size_t i = 1; i < len; i++) {
      ret[i] = tolower(str[i]);
    }
    ret[len - 1] = toupper(ret[len - 1]);
    ret[len] = '\0';
  }
  return ret;
}