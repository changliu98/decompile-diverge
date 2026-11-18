void __cdecl get_grid_address(long *address, const long *address_double, const long *PS)
{
  // Iterate over the 3 spatial dimensions (X, Y, Z)
  for (int i = 0; i < 3; ++i)
  {
    // Calculate the average of the two grid addresses to find the midpoint/center
    address[i] = (address_double[i] - PS[i]) / 2;
  }
}