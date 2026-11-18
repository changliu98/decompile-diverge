static void get_grid_address(long address[3],
                             const long address_double[3],
                             const long PS[3])
{
  int i;

  for (i = 0; i < 3; i++) {
    address[i] = (address_double[i] - PS[i]) / 2;
  }
}