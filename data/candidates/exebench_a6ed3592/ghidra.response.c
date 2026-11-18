void intToString(int n,char *str)

{
  int t_1;
  int t;
  int i;
  char *str_local;
  int n_local;
  
  if (n == 0) {
    *str = '0';
    str[1] = '\0';
  }
  else {
    i = 0;
    for (t = n; t != 0; t = t / 10) {
      i = i + 1;
    }
    str[i] = '\0';
    t_1 = n;
    while (i = i + -1, -1 < i) {
      str[i] = (char)(t_1 % 10) + '0';
      t_1 = t_1 / 10;
    }
  }
  return;
}