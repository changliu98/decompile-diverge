int get_num(int *line, int *num)
{
  int i;
  int count = 0;
  for (i = 0; i < 9; i++)
  {
    if (line[i])
    {
      count++;
      if (num)
        *num = line[i];
    }
  }
  return (count);
}