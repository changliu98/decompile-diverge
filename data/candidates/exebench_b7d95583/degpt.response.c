void mlVectorCrossProductTo(float *vectorA, float *vectorB, float *crossProductResult)
{
  // Calculate the x component of the cross product: a[1]*b[2] - a[2]*b[1]
  crossProductResult[0] = vectorA[1] * vectorB[2] - vectorA[2] * vectorB[1];
  // Calculate the y component of the cross product: a[2]*b[0] - a[0]*b[2]
  crossProductResult[1] = vectorA[2] * vectorB[0] - vectorA[0] * vectorB[2];
  // Calculate the z component of the cross product: a[0]*b[1] - a[1]*b[0]
  crossProductResult[2] = vectorA[0] * vectorB[1] - vectorA[1] * vectorB[0];
}