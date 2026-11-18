int __cdecl func0(int n)
{
  int current_num; 
  int i;
  int total_sevens;

  total_sevens = 0;
  
  for (i = 0; i < n; ++i)
  {
    // Check if the number is a multiple of 11 or 13
    if (i % 11 == 0 || i % 13 == 0)
    {
      // Count how many times the digit '7' appears in the number
      for (current_num = i; current_num > 0; current_num /= 10)
      {
        if (current_num % 10 == 7)
          ++total_sevens;
      }
    }
  }
  
  return total_sevens;
}