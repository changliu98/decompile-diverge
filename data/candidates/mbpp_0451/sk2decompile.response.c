char *func0(char *str) {
  int i = 0, j = 0;
  while (str[i] != '\0') {
    if (!isspace((unsigned char)str[i])) {
      str[j++] = str[i];
    }
    i++;
  }
  str[j] = '\0';
  return str;
}