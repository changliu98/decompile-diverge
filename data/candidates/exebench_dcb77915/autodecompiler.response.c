static float sqrt_sf(float *x)
{
 float y = *x;
 y = __builtin_sqrtf(y);
 return y;
}