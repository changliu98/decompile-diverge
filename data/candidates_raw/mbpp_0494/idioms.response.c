char *to_str(int *test_tup, int size)
{
  int res = 0;
  int i;
  for (i = 0; i < size; i++)
  {
    res += (int)(test_tup[i] * pow(2, size - 1 - i));
  }
  char *res_str = (char *)malloc(sizeof(char)*12);
  sprintf(res_str, "%d", res);
  return res_str;
}