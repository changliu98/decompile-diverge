
static void reduce_grid_address_double(int address[3], const int mesh[3])
{
  int i;

  for (i = 0; i < 3; i++) {

    address[i] -= 2 * mesh[i] * (address[i] > mesh[i]);



  }
}
