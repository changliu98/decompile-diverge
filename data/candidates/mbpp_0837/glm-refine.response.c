int __cdecl func0(int n)
{
  int sum = 0;
  
  // The loop iterates through the first 'n' odd numbers (1, 3, 5, ..., 2n-1)
  // and calculates the sum of their cubes.
  for (int i = 0; i < n; ++i)
  {
    int odd_number = 2 * i + 1;
    sum += odd_number * odd_number * odd_number;
  }
  
  return sum;
}