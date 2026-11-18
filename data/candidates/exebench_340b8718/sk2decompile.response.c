char *strtoupper(char *str) {
  int i;
  char c;
  for (i = 0; i < 8; i++) {
    if (str[i] >= 'a' && str[i] <= 'z')
      c = str[i] - 32;
    else
      c = str[i];
    str[i] = c;
  }
  return str;
}