// Computes the dot product of two 4D vectors A and B
// Returns the sum of the products of their corresponding components
float vec4f_dot(float *vector_a, float *vector_b)
{
    // Calculate dot product: A·B = A[0]*B[0] + A[1]*B[1] + A[2]*B[2] + A[3]*B[3]
    // Note: *A is equivalent to A[0]
    return vector_a[3] * vector_b[3] + vector_a[2] * vector_b[2] + *vector_a * *vector_b + vector_a[1] * vector_b[1];
}