float __cdecl vdot(const float *v1, const float *v2)
{
  return (float)(v1[2] * v2[2]) + (float)((float)(*v1 * *v2) + (float)(v1[1] * v2[1]));
}