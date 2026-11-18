// Function to calculate the sum of all elements in an integer array
// Parameters:
//   arr - pointer to the integer array
//   len - number of elements in the array
// Returns:
//   The sum of all elements in the array
int func0(int *numbers, int count)
{
  int total = 0; // Initialize sum to zero
  for (int index = 0; index < count; index++) { // Iterate through each element of the array
    total += numbers[index]; // Add the current element to the sum
  }
  return total; // Return the calculated sum
}