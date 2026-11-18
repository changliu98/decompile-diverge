char *func0(const char *str, char ch) {
  int len = strlen(str);
  int first = -1, last = -1;
  for (int i = 0; i < len; i++) {
    if (str[i] == ch) {
      if (first == -1) {
        first = i;
      }
      last = i;
    }
  }
  if (first != -1 && last != -1 && first != last) {
    char *new_str = (char *)malloc(len - 2 + 1);
    int new_index = 0;
    for (int i = 0; i < first; i++) {
      new_str[new_index++] = str[i];
    }
    for (int i = first + 1; i < last; i++) {
      new_str[new_index++] = str[i];
    }
    for (int i = last + 1; i < len; i++) {
      new_str[new_index++] = str[i];
    }
    new_str[new_index] = '\0';
    return new_str;
  }
  char *new_str = (char *)malloc(len + 1);
  strcpy(new_str, str);
  return new_str;
}