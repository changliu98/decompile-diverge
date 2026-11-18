int matCalcCross(double *vecA, double *vecB, double *resultVec)
{
    // Calculate the x-component of the cross product: v1[1]*v2[2] - v2[1]*v1[2]
    resultVec[0] = vecA[1] * vecB[2] - vecB[1] * vecA[2];
    // Calculate the y-component of the cross product: v1[2]*v2[0] - v2[2]*v1[0]
    resultVec[1] = vecA[2] * vecB[0] - vecB[2] * vecA[0];
    // Calculate the z-component of the cross product: v1[0]*v2[1] - v2[0]*v1[1]
    resultVec[2] = vecA[0] * vecB[1] - vecB[0] * vecA[1];
    // Return success status
    return 0;
}