int __cdecl func0(int *lst, int size)
{
  int largest = 0;
  int sum = 0;

  // Find the largest prime number in the list
  for (int i = 0; i < size; ++i)
  {
    int num = lst[i];
    if (num > 1)
    {
      int is_prime = 1;
      for (int j = 2; j * j <= num; ++j)
      {
        if (num % j == 0)
        {
          is_prime = 0;
          break;
        }
      }
      
      if (is_prime)
      {
        if (num > largest)
          largest = num;
      }
    }
  }

  // Calculate the sum of the digits of the largest prime
  while (largest > 0)
  {
    sum += largest % 10;
    largest /= 10;
  }

  return sum;
}