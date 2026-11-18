void get_grid_address(long *center, long *pos, long *size)
{
  int i;
  for (i = 0; i < 3; i++)
    center[i] = (pos[i] - size[i]) / 2;
}