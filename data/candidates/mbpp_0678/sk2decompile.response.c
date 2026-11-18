char *func0(char *str) {
  int j = 0;
  int len = strlen(str);
  int i;
  for (i = 0; i < len; i++) {
    if (str[i] != ' ') {
      str[j++] = str[i];
    }
  }
  str[j] = '\0';
  return str;
}