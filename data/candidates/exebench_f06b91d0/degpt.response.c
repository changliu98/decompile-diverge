void add_vector(double *vec1, double *vec2, double *result)
{
    // Iterate through each component of the 3D vectors
    for (int i = 0; i < 3; i++) {
        // Add corresponding components of vectors a and b, store result in out
        result[i] = vec1[i] + vec2[i];
    }
}