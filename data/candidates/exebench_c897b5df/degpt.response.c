/**
 * Scales a 3D vector by a scalar value.
 *
 * @param a       Pointer to the input vector (3 floats).
 * @param b       The scalar multiplier.
 * @param result  Pointer to the output vector (3 floats) to store the scaled result.
 */
void mlVectorScaleTo(float *input_vector, float scalar, float *output_vector)
{
    // Iterate through each component of the 3D vector
    for (uint index = 0; index < 3; index++) {
        // Multiply each component of vector 'a' by scalar 'b' and store in 'result'
        output_vector[index] = input_vector[index] * scalar;
    }
}