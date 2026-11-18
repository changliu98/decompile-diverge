void
mlVectorMultMatrixTo(const float *a, const float *b, float *result)
{
 result[0] = b[0] * a[0] + b[4] * a[1] + b[8] * a[2] + b[12];
 result[1] = b[1] * a[0] + b[5] * a[1] + b[9] * a[2] + b[13];
 result[2] = b[2] * a[0] + b[6] * a[1] + b[10] * a[2] + b[14];
}