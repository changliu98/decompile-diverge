void __cdecl vec3_cross(float *out, const float *a, const float *b)
{
  // X-axis component: out.x = a.y * b.z - a.z * b.y
  out[0] = (a[1] * b[2]) - (a[2] * b[1]);

  // Y-axis component: out.y = a.z * b.x - a.x * b.z
  out[1] = (a[2] * b[0]) - (a[0] * b[2]);

  // Z-axis component: out.z = a.x * b.y - a.y * b.x
  out[2] = (a[0] * b[1]) - (a[1] * b[0]);
}