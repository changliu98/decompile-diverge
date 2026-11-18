// Adds corresponding elements of arrays x and y, storing results in u
// Computes scalar sum: u[0] = x[0] + y[0]
// Computes second element sum: u[1] = x[1] + y[1]
void zadd(double *input_array_a, double *input_array_b, double *output_array)
{
  // Store sum of first elements in u[0]
  *output_array = *input_array_a + *input_array_b;
  // Store sum of second elements in u[1]
  output_array[1] = input_array_a[1] + input_array_b[1];
}