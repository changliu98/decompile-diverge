void func0(char *str) {
  int i, j, len;
  char temp;
  len = strlen(str);
  for (j = 0; j < len - 1; j++) {
    for (i = j + 1; i < len; i++) {
      if (str[j] > str[i]) {
        temp = str[j];
        str[j] = str[i];
        str[i] = temp;
      }
    }
  }
}