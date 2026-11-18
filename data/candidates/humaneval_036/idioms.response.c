int func0()
{
  int count = 0;
  int i = 0;
  for (i = 0; i < n; i++)
  {
    if (i % 11 == 0 || i % 13 == 0)
    {
      int j = i;
      while (j > 0)
      {
        if (j % 10 == 7)
        {
          count++;
        }
        j = j / 10;
      }
    }
  }
  return count;
}