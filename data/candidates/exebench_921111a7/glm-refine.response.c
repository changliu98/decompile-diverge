void __cdecl Vec3Cross(double *vec1, double *vec2, double *vec3)
{
  vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
  vec3[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
  vec3[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}