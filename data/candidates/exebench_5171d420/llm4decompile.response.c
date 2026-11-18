int _inverse_rot(const int32_t *m, int32_t *o)
{
 if (m[1] == 0 || m[2] == 0)
  return 1;

 o[0] = 0;
 o[1] = ((int32_t)(((int32_t)(1 << 20)) / m[2]));
 o[2] = ((int32_t)(((int32_t)(1 << 20)) / m[1]));
 o[3] = 0;
 o[4] = -(m[5] * o[2]) / 1024;
 o[5] = -(m[4] * o[1]) / 1024;

 return 0;
}