// Subtract vector v from vector u (element-wise)
void r3min(double *result, double *subtrahend)
{
  // Subtract first element
  *result -= *subtrahend;
  // Subtract second element
  result[1] -= subtrahend[1];
  // Subtract third element
  result[2] -= subtrahend[2];
}