// Calculates the dot product of two 3D vectors
// vec: pointer to the first vector [x, y, z]
// vec2: pointer to the second vector [x, y, z]
// Returns the scalar dot product: x1*x2 + y1*y2 + z1*z2
float dotproduct(float *vector1, float *vector2)
{
    // Compute dot product: vec[0]*vec2[0] + vec[1]*vec2[1] + vec[2]*vec2[2]
    // *vec and *vec2 access the first element (x-component) of each vector
    return vector1[2] * vector2[2] + *vector1 * *vector2 + vector1[1] * vector2[1];
}