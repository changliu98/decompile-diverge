/**
 * Adds a scaled vector to a final vector.
 *
 * @param factor   The scalar multiplier for the initial vector.
 * @param dim      The dimension (number of elements) of the vectors.
 * @param init_vec The source vector to be scaled and added.
 * @param final_vec The destination vector to which the scaled vector is added.
 */
void add_a_vector(double scalar, int vector_size, double *source_vector, double *destination_vector)
{
    // Iterate through each element of the vectors
    for (int index = 0; index < vector_size; index++) {
        // Update final_vec[i] by adding factor * init_vec[i]
        destination_vector[index] = scalar * source_vector[index] + destination_vector[index];
    }
}