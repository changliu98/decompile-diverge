void reduce_grid_address(int address[3], int mesh[3])
{
  int j;
  for (j = 0; j < 3; j++)
    if (address[j] > mesh[j] / 2) address[j] -= mesh[j];
}