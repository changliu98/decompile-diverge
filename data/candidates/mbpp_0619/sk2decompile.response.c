char *func0(char *str) {
  char *p = str;
  char num[1024];
  int i, j = 0, k = 0;
  for (i = 0; p[i] != '\0'; i++) {
    if (isdigit(p[i])) {
      num[k++] = p[i];
    } else {
      str1[j++] = p[i];
    }
  }
  num[k] = '\0';
  str1[j] = '\0';
  strcat(str1, num);
  return str1;
}