int itoa(char *str, int num) {
  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return 2;
  }
  int len = 0;
  int div = 1;
  int n;
  if (num < 0) {
    n = -num;
  } else {
    n = num;
  }
  while ((n % div) != n) {
    len++;
    div *= 10;
  }
  if (num < 0) {
    len++;
  }
  div = 1;
  for (int i = len - 1; i >= 0; i--) {
    str[i] = (n - (n % div)) / div % 10 + '0';
    div *= 10;
  }
  if (num < 0) {
    str[0] = '-';
  }
  str[len] = '\0';
  return len;
}