void __cdecl addvectors2(float *result, float *vec, float *vec2)
{
  *result = *vec + *vec2;
  result[1] = vec[1] + vec2[1];
}