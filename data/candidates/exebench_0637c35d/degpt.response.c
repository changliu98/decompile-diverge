// Computes the cube of the value pointed to by x and stores the result in the location pointed to by x3
void cube(double *input_value, double *output_value)
{
  // Calculate the cube of the input value and assign it to the output pointer
  *output_value = *input_value * *input_value * *input_value;
}