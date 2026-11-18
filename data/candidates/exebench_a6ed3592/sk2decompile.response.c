void intToString(int n, char *str) {
  if (n == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }
  int i = 0;
  int num = n;
  while (num != 0) {
    i++;
    num /= 10;
  }
  str[i] = '\0';
  i--;
  num = n;
  while (i >= 0) {
    str[i] = (num % 10) + '0';
    i--;
    num /= 10;
  }
}