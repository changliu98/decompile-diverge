static void reduce_grid_address(int address[3], const int mesh[3])
{
  int i;

  for (i = 0; i < 3; i++) {

    address[i] -= mesh[i] * (address[i] > mesh[i] / 2);



  }
}