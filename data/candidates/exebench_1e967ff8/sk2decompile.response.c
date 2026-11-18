void right_shift_str(char *str, int shift) {
  char *p;
  int len = 0;
  char tmp;
  int i, j;
  for (p = str; *p != '\0'; p++) {
    len++;
  }
  for (i = 0; i < shift; i++) {
    tmp = str[len - 1];
    for (j = len - 1; j > 0; j--) {
      str[j] = str[j - 1];
    }
    str[0] = tmp;
  }
}