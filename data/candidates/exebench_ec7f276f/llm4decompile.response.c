void crossproduct(float *result, float *v1, float *v2)
{
 result[0] = v1[1] * v2[2] - v1[2] * v2[1];
 result[1] = v1[2] * v2[0] - v1[0] * v2[2];
 result[2] = v1[0] * v2[1] - v1[1] * v2[0];
}