void getprimes(int startnum, int endnum, int *result, int *result_size)
{
  int i; int j; int isdivisible;
  *result_size = 0;
  for (i = startnum; i <= endnum; i++) {
    isdivisible = 1;
    for (j = i; j > 0; j = j / 10) {
      if (j % 10 == 0 || i % (j % 10) != 0) {
        isdivisible = 0;
        break;
      }
    }
    if (isdivisible) {
      result[*result_size] = i;
      (*result_size)++;
    }
  }
}