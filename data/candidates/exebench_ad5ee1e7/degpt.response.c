/**
 * Computes a 2D cross product-like operation.
 * Given a 2D vector v0 = (v0[0], v0[1]), this function computes a vector r0
 * that is perpendicular to v0 in 2D space, specifically r0 = (-v0[1], v0[0]).
 * This is equivalent to rotating v0 by 90 degrees counter-clockwise.
 *
 * @param v0 Pointer to the input 2D vector (expects at least 2 elements).
 * @param r0 Pointer to the output 2D vector (expects at least 2 elements).
 */
void cross2(float *input_vector, float *output_vector)
{
  // Set the x-component of the result to the negative of v0's y-component
  *output_vector = -input_vector[1];
  // Set the y-component of the result to v0's x-component
  output_vector[1] = *input_vector;
}