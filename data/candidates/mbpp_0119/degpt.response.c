// Function to compute the XOR sum of all elements in the array
int func0(int *numbers, int count)
{
  int index;
  int xorSum = 0; // Initialize XOR accumulator to 0
  for (index = 0; index < count; index = index + 1) {
    xorSum = xorSum ^ numbers[index]; // Compute cumulative XOR of array elements
  }
  return xorSum; // Return the final XOR sum
}