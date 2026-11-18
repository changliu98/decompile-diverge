void reduce_grid_address(long *local, long *mesh)
{
  for (long i = 0; i < 3; i++)
    local[i] -= (local[i] > (mesh[i] / 2)) * mesh[i];
}