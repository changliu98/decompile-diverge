int func0(int n)
{
  int result = 1;
  int i;
  int count;
  int curr_sum;
  int curr_term;
  while (n % 2 == 0)
  {
    n /= 2;
  }
  for (i = 3; i <= sqrt(n)+1; i += 2)
  {
    count = 0;
    curr_sum = 1;
    curr_term = 1;
    while (n % i == 0)
    {
      count += 1;
      n /= i;
      curr_term *= i;
      curr_sum += curr_term;
    }
    result *= curr_sum;
  }
  if (n >= 2)
  {
    result *= n + 1;
  }
  return result;
}