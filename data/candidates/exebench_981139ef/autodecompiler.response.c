void Mat4_vec3_mul(float result[3], const float m[16], const float v[3])
{
  float t[3];
  t[0] = m[0]*v[0] + m[4]*v[1] + m[8 ]*v[2] + m[12];
  t[1] = m[1]*v[0] + m[5]*v[1] + m[9 ]*v[2] + m[13];
  t[2] = m[2]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14];
  memcpy(result, t, sizeof(float)*3);
}