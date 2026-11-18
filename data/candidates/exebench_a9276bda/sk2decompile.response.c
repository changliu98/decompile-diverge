char *intToString(char *str, unsigned int num) {
  int i;
  str[9] = '\0';
  for (i = 8; i >= 0; i--) {
    str[i] = (num % 10) + '0';
    num /= 10;
    if (num == 0) break;
  }
  return &str[i];
}