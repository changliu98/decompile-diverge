char *func0(char *s) {
  int i;
  strcpy(str, s);
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == ' ' || str[i] == ',' || str[i] == '.') str[i] = ':';
  }
  return str;
}