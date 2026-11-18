void od_filter_dering_direction_offsets(int offset[-1], int dir, int bstride)
{
  int i;
  if (dir < 5) {
    for (i = 1; i < 4; i++)
      offset[i-1] = i + i * (dir - 2) / 2 * bstride;
  }
  else {
    for (i = 1; i < 4; i++)
      offset[i-1] = i * (6 - dir) / 2 * bstride + i;
  }
}