void reduce_grid_address_double(int address[3], int mesh[3])
{
  int j;
  for (j = 0; j < 3; j++)
    if (address[j] > mesh[j])
      address[j] = address[j] - 2*mesh[j];
}