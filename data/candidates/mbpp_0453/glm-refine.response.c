int __cdecl func0(int n)
{
  if (n % 2)
    return 0;

  int res = 1;
  int temp_n = n;

  for (int i = 2; i <= (int)sqrt((double)temp_n) + 1; ++i)
  {
    int count = 0;
    int curr_sum = 1;
    int curr_term = 1;

    while (!(temp_n % i))
    {
      ++count;
      temp_n /= i;

      // If the prime factor is 2, exclude the term '2' itself from the sum
      if (i == 2 && count == 1)
        curr_sum = 0;

      curr_term *= i;
      curr_sum += curr_term;
    }
    res *= curr_sum;
  }

  // If there is a remaining prime factor greater than sqrt(n)
  if (temp_n >= 2)
    res *= temp_n + 1;

  return res;
}