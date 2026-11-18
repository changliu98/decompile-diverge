void __cdecl mlVectorCrossProductTo(const float *a, const float *b, float *result)
{
  // X-axis component: a.y * b.z - a.z * b.y
  result[0] = (a[1] * b[2]) - (a[2] * b[1]);

  // Y-axis component: a.z * b.x - a.x * b.z
  result[1] = (a[2] * b[0]) - (a[0] * b[2]);

  // Z-axis component: a.x * b.y - a.y * b.x
  result[2] = (a[0] * b[1]) - (a[1] * b[0]);
}