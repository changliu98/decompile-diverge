int func0(char *s) {
  int len = strlen(s);
  char s2[2 * len + 1];
  strcpy(s2, s);
  strcat(s2, s);
  int i, j, flag, min;
  for (j = 1; j <= len; j++) {
    flag = 1;
    for (i = 0; i < len; i++) {
      if (s[i] != s2[i + j]) {
        flag = 0;
        break;
      }
    }
    if (flag) {
      min = j;
      i = 1;
      break;
    }
  }
  min = len;
  i = 1;
  return min;
}