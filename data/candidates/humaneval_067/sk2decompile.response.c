int _get_num_of_digits(char *str, int len) {
  char num1[10];
  char num2[10];
  int i, j;
  int flag;
  memset(num1, 0, 10);
  memset(num2, 0, 10);
  flag = 0;
  j = 0;
  for (i = 0; str[i] != '\0'; i++) {
    if (isdigit(str[i])) {
      if (flag)
        num2[j++] = str[i];
      else
        num1[j++] = str[i];
    } else {
      if (!flag && j > 0) {
        flag = 1;
        j = 0;
      }
    }
  }
  return len - atoi(num1) - atoi(num2);
}