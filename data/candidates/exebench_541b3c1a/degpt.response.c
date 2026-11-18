// Computes the dot product of two 3D vectors.
// Assumes vectors are stored as [x, y, z] in memory.
// Returns the scalar result of the dot product.
float Vector_Dot_Product(float *vec_a, float *vec_b)
{
    // Calculate dot product: x1*x2 + y1*y2 + z1*z2
    // Note: *vector1 accesses vector1[0] (x-component)
    return vec_a[2] * vec_b[2] + *vec_a * *vec_b + vec_a[1] * vec_b[1];
}