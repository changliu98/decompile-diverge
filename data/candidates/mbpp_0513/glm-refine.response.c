char **__cdecl func0(int *test_tup, int size, char *K)
{
  char **res = (char **)malloc(16LL * size);
  
  for (int i = 0; i < size; ++i)
  {
    asprintf(&res[2 * i], "%d", (unsigned int)test_tup[i]);
    res[2 * i + 1] = K;
  }
  
  return res;
}