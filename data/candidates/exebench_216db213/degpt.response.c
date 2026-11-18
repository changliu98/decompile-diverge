void swapminusfloat(double *first_value, double *second_value)
{
  // Subtract b from a and store the result in a
  *first_value = *first_value - *second_value;
  // Add the new a to b and store the result in b (now b holds the original a)
  *second_value = *first_value + *second_value;
  // Subtract the new a from the new b and store the result in a (now a holds the original b)
  *first_value = *second_value - *first_value;
}