double func0(int *numbers, int count)
{
  int total = 0; // Initialize sum to zero
  for (int i = 0; i < count; i++) { // Iterate through the array
    total += numbers[i]; // Accumulate the sum of array elements
  }
  return (double)total / count; // Return the average as a double
}