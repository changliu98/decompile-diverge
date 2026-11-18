// Adds two double-precision floating-point numbers and stores the result in the memory location pointed to by 'result'.
void ref_add_double(double first_operand, double second_operand, double *output_pointer)
{
  // Compute the sum of arg1 and arg2 and assign it to the value pointed to by result
  *output_pointer = first_operand + second_operand;
}