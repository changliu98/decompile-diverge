int sumdiv(int n)
{
  int i; int res; int na;
  na = n;
  if (na % 2 == 1)
    return 0;
  res = 1;
  for (i = 2; i <= (int)sqrt((double)na)+1; i++)
  {
    int count = 0;
    int curr_sum = 1;
    int curr_term = 1;
    while (na % i == 0)
    {
      count++;
      na /= i;
      if (i == 2 && count == 1)
        curr_sum = 0;
      curr_term *= i;
      curr_sum += curr_term;
    }
    res *= curr_sum;
  }
  if (na >= 2)
    res *= (na + 1);
  return res;
}