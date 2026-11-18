void mlPointAddTo(float *vector_a, float *vector_b, float *sum_vector)
{
    // Add corresponding elements of arrays a and b, storing the result in result
    for (uint index = 0; index < 3; index++) {
        sum_vector[index] = vector_a[index] + vector_b[index];
    }
}