char *is_prime(int n)
{
  int i; int count = 0;
  for (i = 1; i < (int)sqrt((double)n)+2; i++)
  {
    if (n % i == 0)
    {
      if (n / i == i)
      {
        count++;
      }
      else
      {
        count += 2;
      }
    }
  }
  if (count % 2 == 0)
  {
    return "Even";
  }
  else
  {
    return "Odd";
  }
}