void vCross(float *vectorOut, float *vector1, float *vector2)
{
  vectorOut[0] = (vector1[1]*vector2[2]) - (vector1[2]*vector2[1]);
  vectorOut[1] = (vector1[2]*vector2[0]) - (vector1[0]*vector2[2]);
  vectorOut[2] = (vector1[0]*vector2[1]) - (vector1[1]*vector2[0]);
}