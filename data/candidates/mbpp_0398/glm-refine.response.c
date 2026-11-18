int __cdecl func0(int *nums, int length)
{
  int sum = 0;

  for (int i = 0; i < length; ++i)
  {
    int n = nums[i];
    
    // Get the absolute value of the current number
    if (n < 0)
      n = -n;

    // Sum the digits of the number
    while (n > 0)
    {
      sum += n % 10;
      n /= 10;
    }
  }
  
  return sum;
}