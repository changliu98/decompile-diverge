int *count_palindromes_by_parity(int n)
{
  int *counts = (int *)malloc(2 * sizeof(int));
  counts[0] = 0; // Count of even palindromes
  counts[1] = 0; // Count of odd palindromes

  for (int i = 1; i <= n; ++i)
  {
    // Reverse the digits of the current number
    int reversed = 0;
    for (int num = i; num; num /= 10)
      reversed = (reversed * 10) + (num % 10);

    // Check if the number is a palindrome
    if (i == reversed)
    {
      if (i % 2 != 0)
        counts[1]++; // Odd palindrome
      else
        counts[0]++; // Even palindrome
    }
  }
  
  return counts;
}