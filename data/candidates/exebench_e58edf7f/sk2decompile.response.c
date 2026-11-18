void toUpperCase(char *str) {
  int i;
  char c;
  for (i = 0; str[i] != '\0'; i++) {
    for (c = 'a'; c <= 'z'; c++) {
      if (str[i] == c) {
        str[i] = str[i] - 32;
      }
    }
  }
}