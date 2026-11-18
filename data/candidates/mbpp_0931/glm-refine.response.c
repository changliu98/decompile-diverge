double __cdecl func0(int number)
{
  // The expression calculates the sum of the first 'number' integers: n * (n + 1) / 2
  // Then it squares this sum, which is mathematically equivalent to the sum of the cubes of the first 'number' integers.
  double sum = (double)(number * (number + 1)) / 2.0;
  return sum * sum;
}