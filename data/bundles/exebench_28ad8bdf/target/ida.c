void __cdecl matrixApply(float *m, float x, float y, float z, float *outx, float *outy, float *outz)
{
  *outx = (float)((float)(z * m[2]) + (float)((float)(x * *m) + (float)(y * m[1]))) + m[3];
  *outy = (float)((float)(z * m[6]) + (float)((float)(x * m[4]) + (float)(y * m[5]))) + m[7];
  *outz = (float)((float)(z * m[10]) + (float)((float)(x * m[8]) + (float)(y * m[9]))) + m[11];
}