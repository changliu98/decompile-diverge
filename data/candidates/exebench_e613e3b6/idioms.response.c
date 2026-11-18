int cal_intervals(int *stalls, int *intervals, int num)
{
  int i; int j;
  int count = 0;
  for (i = 0; ; i++)
  {
    int stall = 0;
    if (i < num)
      stall = (stalls[i] == 0);
    if (!stall)
      break;
  }
  for (; i < num; i++)
  {
    for ( ; ; i++)
    {
      int stall = 0;
      if (i < num)
        stall = (stalls[i] != 0);
      if (!stall)
        break;
    }
    for (j = 0; ; j++)
    {
      int stall = 0;
      if (i < num)
        stall = (stalls[i] == 0);
      if (!stall)
        break;
      i++;
    }
    if (i < num)
      intervals[count++] = j;
  }
  return count + 1;
}