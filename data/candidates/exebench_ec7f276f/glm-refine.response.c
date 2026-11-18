void __cdecl crossproduct(float *result, const float *vec, const float *vec2)
{
  // X-axis component: result[0] = (vec2[1] * vec[2]) - (vec2[2] * vec[1])
  result[0] = (vec2[1] * vec[2]) - (vec2[2] * vec[1]);

  // Y-axis component: result[1] = (vec2[2] * vec[0]) - (vec2[0] * vec[2])
  result[1] = (vec2[2] * vec[0]) - (vec2[0] * vec[2]);

  // Z-axis component: result[2] = (vec2[0] * vec[1]) - (vec2[1] * vec[0])
  result[2] = (vec2[0] * vec[1]) - (vec2[1] * vec[0]);
}