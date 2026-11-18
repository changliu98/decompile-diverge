char *func0(char *str) {
  if (str == NULL) {
    return NULL;
  } else {
    size_t len = strlen(str);
    char *compressed_str = malloc(len + 1);
    if (compressed_str == NULL) {
      return NULL;
    } else {
      int j = 0,
          space_found = 0;
      for (int i = 0;; i++) {
        if (str[i] == '\0') {
          compressed_str[j] = '\0';
          break;
        } else if (str[i] != ' ') {
          compressed_str[j++] = str[i];
          space_found = 0;
        } else if (!space_found) {
          compressed_str[j++] = ' ';
          space_found = 1;
        }
      }
      return compressed_str;
    }
  }
}