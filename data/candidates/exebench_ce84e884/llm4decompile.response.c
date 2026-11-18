void get_grid_address(long address[3], double address_double[3], long PS[3])
{
  int i;
  for (i = 0; i < 3; i++)
    address[i] = (long) (address_double[i] - PS[i]) / 2;
}