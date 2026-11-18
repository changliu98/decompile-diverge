int func0(char *str) {
  int count = 0;
  int len = strlen(str);
  int i, j;
  for (i = 0; i < len; i++) {
    for (j = 1; j <= len - i; j++) {
      if (check_Equality(str, i, i + j - 1)) {
        count++;
      }
    }
  }
  return count;
}