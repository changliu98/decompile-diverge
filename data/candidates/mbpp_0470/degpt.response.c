// Computes the sum of adjacent elements in test_tup and stores the result in result array
// Parameters:
//   test_tup - input array of integers
//   size     - number of elements in test_tup
//   result   - output array to store the sums of adjacent elements
void func0(int *input_array, int array_length, int *output_array)
{
  // Iterate through the array up to the second-to-last element
  for (int index = 0; index < array_length - 1; index++) {
    // Store the sum of current and next element in the result array
    output_array[index] = input_array[index] + input_array[index + 1];
  }
}