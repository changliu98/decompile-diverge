void vinv(double *vector)
{
  // Negate the first element of the vector
  *vector = -*vector;
  // Negate the second element of the vector
  vector[1] = -vector[1];
  // Negate the third element of the vector
  vector[2] = -vector[2];
}