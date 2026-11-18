// Adds the elements of the delta array to the corresponding elements of the v array.
void atmtns(double *increments, double *values)
{
  // Add the first element of delta to the first element of v
  *values += *increments;
  // Add the second element of delta to the second element of v
  values[1] += increments[1];
  // Add the third element of delta to the third element of v
  values[2] += increments[2];
}