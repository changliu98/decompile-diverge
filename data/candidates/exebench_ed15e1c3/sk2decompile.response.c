void reverse(char *str) {
  unsigned int i, len;
  char tmp;
  for (i = 0; str[i]; i++)
    ;
  len = i;
  for (i = 0; i < len / 2; i++) {
    tmp = str[i];
    str[i] = str[len - (i + 1)];
    str[len - (i + 1)] = tmp;
  }
}