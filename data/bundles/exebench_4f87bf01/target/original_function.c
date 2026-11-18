static void reduce_grid_address(long address[3], const long mesh[3])
{
  long i;

  for (i = 0; i < 3; i++) {

    address[i] -= mesh[i] * (address[i] > mesh[i] / 2);



  }
}