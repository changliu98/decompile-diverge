int func0(int *data, int length)
{
  int i;
  int j;
  for (i = 0; i < length; i++)
  {
    for (j = i + 1; j < length; j++)
    {
      if (data[i] == data[j])
      {
        return 0;
      }
    }
  }
  return 1;
}