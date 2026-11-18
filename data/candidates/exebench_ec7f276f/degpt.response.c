void crossproduct(float *output, float *vector1, float *vector2)
{
    // Calculate the x-component of the cross product
    output[0] = vector2[1] * vector1[2] - vector2[2] * vector1[1];
    // Calculate the y-component of the cross product
    output[1] = vector2[2] * vector1[0] - vector2[0] * vector1[2];
    // Calculate the z-component of the cross product
    output[2] = vector2[0] * vector1[1] - vector2[1] * vector1[0];
}