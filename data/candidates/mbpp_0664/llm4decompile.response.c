int func0(int n)
{
  int count = 0;
  int sm = 0;
  int avg;

  if (n % 2 != 0)
    {
      printf("Invalid Input\n");
      return -1;
    }

  while (n > 1)
    {
      sm = sm + n;
      n = n - 2;
      count = count + 1;
    }
  avg = sm / count;
  return avg;
}