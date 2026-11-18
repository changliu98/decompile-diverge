int func0(int n) {
  char str[20];
  int i, len, nn, flag;
  nn = n;
  for (i = n + 1; i != 0x7fffffff; i++) {
    sprintf(str, "%d", i);
    len = strlen(str);
    flag = 1;
    for (int j = 0; j < len / 2; j++) {
      if (str[j] != str[len - 1 - j]) {
        flag = 0;
        break;
      }
    }
    if (flag) {
      return i;
    }
  }
  return -1;
}