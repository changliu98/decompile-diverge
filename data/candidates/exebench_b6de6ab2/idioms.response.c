void reduce_grid_address(int *point, int *mesh)
{
  int i;
  for (i = 0; i < 3; i++)
    if (point[i] > (mesh[i] / 2))
      point[i] -= mesh[i];
}