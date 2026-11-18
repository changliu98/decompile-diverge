int func0(int n)
{
  int index;
  int sum_of_fifth_powers = 0;
  
  // Loop from 1 to n, calculating the sum of fifth powers
  for (index = 1; index <= n; index = index + 1) {
    // Add i^5 to the running sum
    sum_of_fifth_powers = index * index * index * index * index + sum_of_fifth_powers;
  }
  return sum_of_fifth_powers;
}