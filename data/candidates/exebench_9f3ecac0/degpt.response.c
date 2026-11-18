// Copies the first three elements from array v to array u
void r3cp(double *destination, double *source)
{
  // Copy the first element
  *destination = *source;
  // Copy the second element
  destination[1] = source[1];
  // Copy the third element
  destination[2] = source[2];
}