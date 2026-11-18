char *_remove_char(char *str, char c) {
  int len = strlen(str);
  int first = -1;
  int last = -1;
  int i;
  for (i = 0; i < len; i++) {
    if (str[i] == c) {
      if (first == -1) {
        first = i;
      }
      last = i;
    }
  }
  if (first == -1 || last == -1 || first == last) {
    char *new_str = malloc(len + 1);
    strcpy(new_str, str);
    return new_str;
  }
  char *new_str = malloc(len - 2 + 1);
  int j = 0;
  for (i = 0; i < first; i++) {
    new_str[j++] = str[i];
  }
  for (i = first + 1; i < last; i++) {
    new_str[j++] = str[i];
  }
  for (i = last + 1; i < len; i++) {
    new_str[j++] = str[i];
  }
  new_str[j] = '\0';
  return new_str;
}