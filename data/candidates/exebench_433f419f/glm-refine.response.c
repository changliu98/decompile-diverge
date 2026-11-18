void __cdecl subtractvectors(float *result, float *vec, float *vec2)
{
  result[0] = vec[0] - vec2[0];
  result[1] = vec[1] - vec2[1];
  result[2] = vec[2] - vec2[2];
}