int func0(int n)
{
  int digit_count = 0; // Initialize counter to zero
  for (; n != 0; n /= 10) { // Loop until n becomes zero, dividing n by 10 in each iteration
    digit_count++; // Increment counter for each digit processed
  }
  return digit_count; // Return the total number of digits in n
}