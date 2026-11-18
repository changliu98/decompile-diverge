char *func0(char *str, char c1, char c2) {
  static char str2[100];
  int i;
  strcpy(str2, str);
  for (i = 0; i < strlen(str2); i++) {
    if (str2[i] == c1) str2[i] = c2;
  }
  return str2;
}