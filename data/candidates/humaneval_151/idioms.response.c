static long func0(float *lst, int lst_size)
{
  long sum = 0;
  int i;
  for (i = 0; i < lst_size; i++) {
    if (lst[i] - round(lst[i]) < 0.0001 && lst[i] > 0
        && round(lst[i]) % 2 == 1) {
      int n = (int)round(lst[i]);
      sum += n * n;
    }
  }
  return sum;
}