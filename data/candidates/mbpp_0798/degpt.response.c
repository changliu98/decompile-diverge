// Function to calculate the sum of elements in an integer array
// Parameters:
//   arr - pointer to the first element of the array
//   n   - number of elements in the array
// Returns:
//   The sum of all elements in the array
int func0(int *numbers, int count)
{
  int total = 0; // Initialize sum to zero
  for (int index = 0; index < count; index++) { // Iterate through each element of the array
    total += numbers[index]; // Add current element to sum
  }
  return total; // Return the calculated sum
}