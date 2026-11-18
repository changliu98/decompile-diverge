int func0(int n) {
  int i, len, j;
  char str[12], str1[12], temp;
  int num = n;
  for (j = n - 1; j > 0; j--) {
    sprintf(str, "%d", j);
    strcpy(str1, str);
    len = strlen(str1);
    for (i = 0; i < len / 2; i++) {
      temp = str1[i];
      str1[i] = str1[len - 1 - i];
      str1[len - 1 - i] = temp;
    }
    if (!strcmp(str, str1)) return j;
  }
  return 0;
}