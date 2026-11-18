void ft_25_lines(char *c, float *sign, float *res, int *i) {
  i[1] = *c - 48;
  if (i[1] >= 0 && i[1] <= 9) {
    if (i[0] == 1) *sign = *sign / 10;
    *res = *res * 10 + i[1];
  }
}