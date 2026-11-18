int average(int n)
{
  int i = n;
  int sum;
  int count;
  if (i % 2 == 0)
  {
    printf("Invalid Input\n");
    return -1;
  }
  else
  {
    sum = 0;
    count = 0;
    while (i >= 1)
    {
      count++;
      sum += i;
      i -= 2;
    }
    return (sum / count);
  }
}