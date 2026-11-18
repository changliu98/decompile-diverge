// Computes the dot product of two 3D vectors A and B.
// The vectors are assumed to be stored in memory order [z, x, y].
// Returns the scalar dot product: A.z*B.z + A.x*B.x + A.y*B.y.
float vec3f_dot(float *vector_a, float *vector_b)
{
    return vector_a[2] * vector_b[2] + *vector_a * *vector_b + vector_a[1] * vector_b[1];
}