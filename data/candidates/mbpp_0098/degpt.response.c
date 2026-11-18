double func0(int *input_array,int array_length)
{
  int index;
  // Initialize total with a constant value
  double product_accumulator = initial_constant;
  // Iterate through the array and multiply each element by the current total
  for (index = 0; index < array_length; index++) {
    product_accumulator = (double)input_array[index] * product_accumulator;
  }
  // Return the final total divided by the size of the array
  return product_accumulator / (double)array_length;
}