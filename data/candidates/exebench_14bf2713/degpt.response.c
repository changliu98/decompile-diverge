void Vector_Cross_Product(float *result, float *vectorA, float *vectorB)
{
    // Calculate the x-component of the cross product: (v1_y * v2_z) - (v1_z * v2_y)
    result[0] = vectorA[1] * vectorB[2] - vectorA[2] * vectorB[1];
    // Calculate the y-component of the cross product: (v1_z * v2_x) - (v1_x * v2_z)
    result[1] = vectorA[2] * vectorB[0] - vectorA[0] * vectorB[2];
    // Calculate the z-component of the cross product: (v1_x * v2_y) - (v1_y * v2_x)
    result[2] = vectorA[0] * vectorB[1] - vectorA[1] * vectorB[0];
}