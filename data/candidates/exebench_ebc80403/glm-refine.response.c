vec1 * value
void __cdecl Vec3MultValue(double *vec1, double value, double *vec2)
{
  vec2[0] = vec1[0] * value;
  vec2[1] = vec1[1] * value;
  vec2[2] = vec1[2] * value;
}