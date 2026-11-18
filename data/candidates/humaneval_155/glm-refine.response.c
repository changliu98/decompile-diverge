void __cdecl count_even_odd_digits(int num, int *result)
{
  int odd_count;
  int even_count;
  int current_num;

  even_count = 0;
  odd_count = 0;
  current_num = abs(num);
  
  do
  {
    // Check if the last digit is odd
    if (current_num % 10 % 2)
      ++odd_count;
    else
      ++even_count;
      
    // Remove the last digit
    current_num /= 10;
  }
  while (current_num > 0);
  
  // Store the results in the output array
  result[0] = even_count;
  result[1] = odd_count;
}