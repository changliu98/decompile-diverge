void
mlMatrixMultVectorTo(const float *a, const float *b, float *result)
{
 result[0] = a[0] * b[0] + a[4] * b[1] + a[8] * b[2] + a[12];
 result[1] = a[1] * b[0] + a[5] * b[1] + a[9] * b[2] + a[13];
 result[2] = a[2] * b[0] + a[6] * b[1] + a[10] * b[2] + a[14];
}