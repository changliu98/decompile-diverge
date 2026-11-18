static void motion_V(int *pred, int r_size, int motion_code, int motion_r, int full_pel_vector)
{
  int max = (1 << r_size) * 16;
  int v = (full_pel_vector ? *pred >> 1 : *pred);
  int v1 = v;
  if (motion_code > 0)
  {
    v1 = v + motion_r + (motion_code - 1) * (1 << r_size) + 1;
    if (v1 >= max)
      v1 -= 2 * max;
  }
  else if (motion_code < 0)
  {
    v1 = v - (motion_r + (motion_code + 1) * (1 << r_size) + 1);
    if (v1 < -max)
      v1 += 2 * max;
  }
  *pred = (full_pel_vector ? v1 * 2 : v1);
}