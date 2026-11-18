int func0(int target)
{
  int divisor_sum = 1; // Initialize sum with 1, as 1 is a proper divisor of any number greater than 1
  for (int divisor = 2; divisor < target; divisor++) { // Iterate from 2 to number-1 to find proper divisors
    if (target % divisor == 0) { // Check if i is a divisor of number
      divisor_sum += divisor; // Add the divisor to the sum
    }
  }
  return divisor_sum; // Return the sum of all proper divisors
}