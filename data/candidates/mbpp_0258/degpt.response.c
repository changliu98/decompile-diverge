// Function to count the number of odd integers in an array
int func0(int *numbers, int size)
{
  int odd_count = 0; // Initialize counter for odd numbers
  for (int index = 0; index < size; index++) { // Iterate through each element in the array
    if (numbers[index] % 2 != 0) { // Check if the current element is odd
      odd_count++; // Increment the odd number counter
    }
  }
  return odd_count; // Return the total count of odd numbers
}