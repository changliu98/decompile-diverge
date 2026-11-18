/**
 * @brief Multiplies a 3-element vector by a scalar.
 *
 * @param u Output vector (result of v * c).
 * @param v Input vector to be scaled.
 * @param c Scalar multiplier.
 */
void r3cpsc(double *result, double *input_vector, double scalar)
{
    *result = *input_vector * scalar;      // Multiply first element of v by c and store in first element of u
    result[1] = input_vector[1] * scalar;  // Multiply second element of v by c and store in second element of u
    result[2] = input_vector[2] * scalar;  // Multiply third element of v by c and store in third element of u
}