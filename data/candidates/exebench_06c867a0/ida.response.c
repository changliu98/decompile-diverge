float __cdecl dotproduct(float *vec, float *vec2)
{
  return (float)(vec[2] * vec2[2]) + (float)((float)(*vec * *vec2) + (float)(vec[1] * vec2[1]));
}