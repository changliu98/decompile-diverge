char *func0(char *str) {
  int j = 0;
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] < 'a' || str[i] > 'z') {
      str1[j++] = str[i];
    }
  }
  str1[j] = '\0';
  return str1;
}