void __cdecl mlMatrixMultVectorTo(const float *a, const float *b, float *result)
{
  *result = (float)((float)(a[8] * b[2]) + (float)((float)(*a * *b) + (float)(a[4] * b[1]))) + a[12];
  result[1] = (float)((float)(a[9] * b[2]) + (float)((float)(a[1] * *b) + (float)(a[5] * b[1]))) + a[13];
  result[2] = (float)((float)(a[10] * b[2]) + (float)((float)(a[2] * *b) + (float)(a[6] * b[1]))) + a[14];
}