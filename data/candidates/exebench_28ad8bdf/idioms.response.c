void matrixApply(float m[16], float x, float y, float z, float *outx, float *outy, float *outz)
{
  *outx = m[0] * x + m[1] * y + m[2] * z + m[3];
  *outy = m[4] * x + m[5] * y + m[6] * z + m[7];
  *outz = m[8] * x + m[9] * y + m[10] * z + m[11];
}