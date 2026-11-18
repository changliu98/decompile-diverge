// Function to find the maximum value in an integer array
int func0(int *array, int length)
{
  int index;
  // Initialize max_val to the minimum possible integer value
  int maximum_value = -0x80000000;
  
  // Iterate through the array to find the maximum value
  for (index = 0; index < length; index = index + 1) {
    // Update max_val if the current element is greater
    if (maximum_value < array[index]) {
      maximum_value = array[index];
    }
  }
  // Return the maximum value found
  return maximum_value;
}