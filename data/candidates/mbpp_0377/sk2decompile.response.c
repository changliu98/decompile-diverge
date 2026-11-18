char *_remove_char(char *str, char c) {
  int count = 0;
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == c) {
      count++;
    }
  }
  char *new_str = malloc(strlen(str) - count + 1);
  int j = 0;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] != c) {
      new_str[j] = str[i];
      j++;
    }
  }
  new_str[j] = '\0';
  return new_str;
}