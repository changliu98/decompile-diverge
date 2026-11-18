char *get_begin(char *str, int *sign) {
  int i;
  int s;
  i = 0;
  s = 1;
  while (str[i] == '+' || str[i] == '-') {
    if (str[i] == '-') s *= -1;
    i++;
  }
  *sign = s;
  return (str + i);
}