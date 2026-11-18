void reduce_grid_address_double(int *a, int *mesh)
{
  int i;
  for (i = 0; i < 3; i++)
    a[i] -= (a[i] > mesh[i]) * mesh[i] * 2;
}