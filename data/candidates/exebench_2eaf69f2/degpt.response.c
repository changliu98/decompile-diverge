void vec3Cross(double *vectorA, double *vectorB, double *resultVector)
{
    // Calculate the x-component of the cross product: v[1]*w[2] - w[1]*v[2]
    resultVector[0] = vectorA[1] * vectorB[2] - vectorB[1] * vectorA[2];
    // Calculate the y-component of the cross product: w[0]*v[2] - v[0]*w[2]
    resultVector[1] = vectorB[0] * vectorA[2] - vectorA[0] * vectorB[2];
    // Calculate the z-component of the cross product: v[0]*w[1] - w[0]*v[1]
    resultVector[2] = vectorA[0] * vectorB[1] - vectorB[0] * vectorA[1];
}