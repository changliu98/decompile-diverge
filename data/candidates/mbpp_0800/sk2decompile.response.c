void _remove_whitespace(char *str, char *result) {
  int i = 0, j = 0;
  while (str[i] != '\0') {
    if (!isspace((unsigned char)str[i])) {
      result[j++] = str[i];
    }
    i++;
  }
  result[j] = '\0';
}