// Calculates the dot product of two 4D vectors.
// lhs: Pointer to the first 4D vector (x, y, z, w).
// rhs: Pointer to the second 4D vector (x, y, z, w).
// Returns: The scalar dot product of the two vectors.
float vec4DotProduct(float *vectorA, float *vectorB)
{
    // Compute dot product: x1*x2 + y1*y2 + z1*z2 + w1*w2
    // Note: *lhs is equivalent to lhs[0]
    return vectorA[3] * vectorB[3] + vectorA[2] * vectorB[2] + *vectorA * *vectorB + vectorA[1] * vectorB[1];
}