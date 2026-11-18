void reverse(char *str) {
  int i = 0;
  int len = 0;
  while (str[i++] != '\0') {
    len++;
  }
  int j;
  for (j = 0; j < len / 2; j++) {
    char temp = str[j];
    str[j] = str[len - 1 - j];
    str[len - 1 - j] = temp;
  }
}