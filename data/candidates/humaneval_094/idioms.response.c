int func0(int *list, int size)
{
  int i; int j; int prime; int num; int largest = 0; int sum = 0;
  for (i = 0; i < size; i++)
  {
    num = list[i];
    if (num > 1)
    {
      prime = 1;
      for (j = 2; j * j <= num; j++)
      {
        if (num % j == 0)
        {
          prime = 0;
          break;
        }
      }
      if (prime)
      {
        if (num > largest)
        {
          largest = list[i];
        }
        else
        {
          largest = largest;
        }
      }
    }
  }
  while (largest > 0)
  {
    sum += largest % 10;
    largest = largest / 10;
  }
  return sum;
}