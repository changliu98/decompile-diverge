char* func0(int n) {
  char str[6];
  sprintf(str, "%d", n);
  int sum = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    sum += str[i] - '0';
  }
  char* res = (char*)malloc(33);
  int len = 0;
  if (sum == 0) {
    len = 1;
    res[0] = '0';
  } else {
    while (sum > 0) {
      res[len++] = (sum % 2) + '0';
      sum /= 2;
    }
  }
  res[len] = '\0';
  for (int i = 0; i < len / 2; i++) {
    char tmp = res[i];
    res[i] = res[len - i - 1];
    res[len - i - 1] = tmp;
  }
  return res;
}