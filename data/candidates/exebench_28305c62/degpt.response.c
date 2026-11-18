// Calculates the dot product of two 3D vectors.
// The vectors are represented as arrays of 3 floats.
// The function assumes the vectors are stored in the order [z, x, y].
// Parameters:
//   lhs: Pointer to the first 3D vector.
//   rhs: Pointer to the second 3D vector.
// Returns:
//   The dot product of the two vectors.
float vec3DotProduct(float *vector1, float *vector2)
{
    // Compute the dot product: z1*z2 + x1*x2 + y1*y2
    // Note: The array order is [z, x, y], so index 0 is z, index 1 is x, index 2 is y.
    // However, the code uses lhs[2] and rhs[2] for the first term, which corresponds to y.
    // And *lhs and *rhs correspond to index 0, which is z.
    // And lhs[1] and rhs[1] correspond to x.
    // So the calculation is: y1*y2 + z1*z2 + x1*x2, which is equivalent to the standard dot product.
    return vector1[2] * vector2[2] + *vector1 * *vector2 + vector1[1] * vector2[1];
}