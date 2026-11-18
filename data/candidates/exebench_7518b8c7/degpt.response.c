// Function to find the index of the maximum value in the first two elements of the array
int max(float *input_array)
{
  int max_index = 0; // Initialize return value to index 0
  float max_value = *input_array; // Initialize highest value to the first element of the array
  for (int current_index = 1; current_index < 2; current_index++) { // Iterate through the second element (index 1)
    if (max_value < input_array[current_index]) { // Check if current element is greater than the highest found so far
      max_index = current_index; // Update return value to current index
      max_value = input_array[current_index]; // Update highest value to current element
    }
  }
  return max_index; // Return the index of the maximum value
}