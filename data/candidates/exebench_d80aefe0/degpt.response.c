// Computes the dot product of two 3D vectors a and b
// Returns the sum of the products of corresponding components: a[0]*b[0] + a[1]*b[1] + a[2]*b[2]
float vdot(float *vec_a, float *vec_b)
{
    // Calculate dot product: a[0]*b[0] + a[1]*b[1] + a[2]*b[2]
    // Note: *a is equivalent to a[0]
    return vec_a[2] * vec_b[2] + *vec_a * *vec_b + vec_a[1] * vec_b[1];
}