// Computes the dot product of two 3D vectors v1 and v2
// Returns the sum of the products of corresponding components: v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]
float vdot(float *vec_a, float *vec_b)
{
    // Calculate dot product: x*x + y*y + z*z
    return vec_a[2] * vec_b[2] + *vec_a * *vec_b + vec_a[1] * vec_b[1];
}