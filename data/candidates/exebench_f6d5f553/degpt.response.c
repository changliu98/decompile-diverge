// Computes the dot product of two 3D vectors.
// Parameters:
//   a - Pointer to the first 3D vector (x, y, z)
//   b - Pointer to the second 3D vector (x, y, z)
// Returns:
//   The scalar dot product of vectors a and b.
float vector3d_dot(float *vec_a, float *vec_b)
{
    // Calculate dot product: a.x*b.x + a.y*b.y + a.z*b.z
    // Note: *a accesses a[0] (x component), a[1] is y, a[2] is z
    return vec_a[2] * vec_b[2] + *vec_a * *vec_b + vec_a[1] * vec_b[1];
}