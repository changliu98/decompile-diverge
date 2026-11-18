void all_ge_zero(double *begin, double *end, double *res)
{
  int i;
  *res = 1;
  for (i = 0; i < (end - begin + 1); i++) {
    int cond = 0;
    if (*res == 1) {
      cond = (begin[i] >= 0);
    }
    *res = cond;
  }
}