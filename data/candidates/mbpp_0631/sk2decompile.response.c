void _replace_spaces(char *str) {
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == ' ') {
      str[i] = '_';
    }
  }
}