void vector3d_cross(float *vecA, float *vecB, float *result)
{
    // Calculate the x-component of the cross product: a[1]*b[2] - a[2]*b[1]
    result[0] = vecA[1] * vecB[2] - vecA[2] * vecB[1];
    // Calculate the y-component of the cross product: a[2]*b[0] - a[0]*b[2]
    result[1] = vecA[2] * vecB[0] - vecA[0] * vecB[2];
    // Calculate the z-component of the cross product: a[0]*b[1] - a[1]*b[0]
    result[2] = vecA[0] * vecB[1] - vecA[1] * vecB[0];
}