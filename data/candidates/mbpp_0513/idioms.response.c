char **func0(int *test_tup, int size, char *sep)
{
  char **res = (char **)malloc(size * 2 * sizeof(char *));
  int i = 0;
  int j = 0;
  for (i = 0; i < size; i++)
  {
    asprintf(&res[j], "%d", test_tup[i]);
    res[++j] = sep;
  }
  return res;
}