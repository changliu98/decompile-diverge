// Subtract vector b from vector a element-wise
void mlVectorSub(float *vector_a, float *vector_b)
{
    // Iterate over each component of the 3D vector
    for (uint index = 0; index < 3; index++) {
        // Subtract the corresponding element of b from a
        vector_a[index] -= vector_b[index];
    }
}