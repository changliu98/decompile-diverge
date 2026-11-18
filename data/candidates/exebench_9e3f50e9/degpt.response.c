// Adds elements of array 'a' to array 'b' in chunks of 4 for potential vectorization
void AddArray4(float *source_array, float *target_array, int array_length)
{
  // Iterate through the arrays with a stride of 4 to process 4 elements per iteration
  for (int index = 0; index < array_length; index += 4) {
    target_array[index] += source_array[index];       // Add current element of 'a' to 'b'
    target_array[index + 1] += source_array[index + 1]; // Add next element of 'a' to 'b'
    target_array[index + 2] += source_array[index + 2]; // Add next element of 'a' to 'b'
    target_array[index + 3] += source_array[index + 3]; // Add next element of 'a' to 'b'
  }
}