int func0(int n)
{
  int total = 0; // Initialize sum to 0
  for (int counter = 1; counter <= n; counter++) { // Loop from 1 to n
    total += counter * counter * counter * counter; // Add the fourth power of i to sum
  }
  return total; // Return the calculated sum
}