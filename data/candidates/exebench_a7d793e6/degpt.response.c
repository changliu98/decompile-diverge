void subtract(float *vector_a, float *vector_b, float *result_vector)
{
    // Calculate the difference of the first elements of vectors u and v, store in r
    *result_vector = *vector_a - *vector_b;
    // Calculate the difference of the second elements of vectors u and v, store in r
    result_vector[1] = vector_a[1] - vector_b[1];
    // Calculate the difference of the third elements of vectors u and v, store in r
    result_vector[2] = vector_a[2] - vector_b[2];
}