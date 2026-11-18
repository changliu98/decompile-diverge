int func0(int n)
{
  int sum = 0;
  int count = 0;
  int temp = n;
  if (temp % 2 == 1)
  {
    printf("Invalid Input\n");
    return -1;
  }
  else
  {
    while (temp >= 2)
    {
      count++;
      sum += temp;
      temp -= 2;
    }
    return sum / count;
  }
}