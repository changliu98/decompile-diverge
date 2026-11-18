// Function to count the number of non-negative integers in the given list
int func0(int *numbers, int num_elements)
{
  int non_negative_count = 0; // Initialize counter for non-negative elements
  for (int index = 0; index < num_elements; index++) { // Iterate through each element in the list
    if (numbers[index] > -1) { // Check if the current element is non-negative
      non_negative_count++; // Increment the counter for non-negative elements
    }
  }
  return non_negative_count; // Return the total count of non-negative elements
}