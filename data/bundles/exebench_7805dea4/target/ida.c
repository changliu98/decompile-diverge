void __cdecl mlVectorMultMatrixTo(const float *a, const float *b, float *result)
{
  *result = (float)((float)(b[8] * a[2]) + (float)((float)(*b * *a) + (float)(b[4] * a[1]))) + b[12];
  result[1] = (float)((float)(b[9] * a[2]) + (float)((float)(b[1] * *a) + (float)(b[5] * a[1]))) + b[13];
  result[2] = (float)((float)(b[10] * a[2]) + (float)((float)(b[2] * *a) + (float)(b[6] * a[1]))) + b[14];
}