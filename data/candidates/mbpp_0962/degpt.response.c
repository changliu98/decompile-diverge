// Calculates the sum of even numbers in the range [l, r]
// Formula: sum of even numbers up to n is (n/2) * (n/2 + 1)
// Result is sum_even(r) - sum_even(l-1)
int calculate_even_sum(int lower_bound, int upper_bound)
{
  // Sum of even numbers from 1 to r minus sum of even numbers from 1 to l-1
  return (upper_bound / 2) * (upper_bound / 2 + 1) - (((lower_bound - 1) / 2) * (lower_bound + 1)) / 2;
}