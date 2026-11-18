int func0(int *test_tuple, int tuple_size, int *K, int K_size)
{
  int i;
  int j;
  int found;
  for (i = 0; i < tuple_size; i++)
  {
    found = 0;
    for (j = 0; j < K_size; j++)
    {
      if (test_tuple[i] == K[j])
      {
        found = 1;
        break;
      }
    }
    if (!found)
    {
      return 0;
    }
  }
  return 1;
}