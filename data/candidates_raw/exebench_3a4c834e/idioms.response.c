void tri_to_ver(float x, float y, float z, float *ver)
{
  float x1 = x + ( -z * 0.5);
  ver[1] = x + z;
  ver[0] = x1 + ( y * 0.86602538);
  ver[2] = x1 - ( y * 0.86602538);
}