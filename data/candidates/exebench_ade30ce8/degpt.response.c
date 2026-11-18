void cross_product(float *vector_a, float *vector_b, float *result)
{
    // Calculate the x-component of the cross product
    result[0] = vector_a[1] * vector_b[2] - vector_a[2] * vector_b[1];
    // Calculate the y-component of the cross product
    result[1] = vector_a[2] * vector_b[0] - vector_a[0] * vector_b[2];
    // Calculate the z-component of the cross product
    result[2] = vector_a[0] * vector_b[1] - vector_a[1] * vector_b[0];
}