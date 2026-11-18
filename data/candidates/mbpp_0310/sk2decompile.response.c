char *func0(char *str, char *str2) {
  int i, j = 0;
  for (i = 0; i < strlen(str); i++) {
    if (!isspace(str[i])) {
      str2[j++] = str[i];
    }
  }
  str2[j] = '\0';
  return str2;
}