float dotProduct(int length, float *v1, float *v2)
{
 int i;
 float result = 0.0;

 for (i = 0; ; i++) {
  if (i >= length) break;
  result += v1[i] * v2[i];
 }

 return result;
}