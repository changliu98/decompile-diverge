static float _sqrt(float *x)
{
 float y = *x;
 y = __builtin_sqrtf(y);
 return y;
}