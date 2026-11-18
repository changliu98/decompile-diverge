int __cdecl func0(int *nums, int size)
{
  int count = 0;
  
  for (int i = 0; i < size; ++i)
  {
    if (nums[i] > 10)
    {
      int most_significant_digit = nums[i];
      
      // Extract the first (most significant) digit
      while (most_significant_digit >= 10)
      {
        most_significant_digit /= 10;
      }
      
      int last_digit = nums[i] % 10;
      
      // Check if both the first and last digits are odd
      if (most_significant_digit % 2 == 1 && last_digit % 2 == 1)
      {
        ++count;
      }
    }
  }
  
  return count;
}