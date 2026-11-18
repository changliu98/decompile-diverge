// Function to perform a scaled addition operation on arrays
// n: number of elements in the arrays
// a: scaling factor
// x: input array
// y: output array (also used as accumulator)
void f1(int num_elements, float scale_factor, float *input_array, float *output_array)
{
  int index;
  // Iterate through each element of the arrays
  for (index = 0; index < num_elements; index++) {
    // Update y[i] by adding the product of a and x[i] to the current value of y[i]
    output_array[index] = scale_factor * input_array[index] + output_array[index];
  }
}