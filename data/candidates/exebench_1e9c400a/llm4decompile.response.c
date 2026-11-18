void myArrayDiv(float *src, float divisor, float *result)
{
 int i;
 for (i = 0; i < 5; i++)
 {
  result[i] = src[i] / divisor;
 }
}