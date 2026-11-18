char func0(char *str) {
  int i, count, j, len;
  len = strlen(str);
  for (j = 0; j < len; j++) {
    count = 0;
    for (i = 0; i <= j; i++) {
      if (str[i] == str[j]) count++;
    }
    if (count > 1) return str[j];
  }
  return '0';
}