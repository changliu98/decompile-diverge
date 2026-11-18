void __cdecl reduce_grid_address(int *address, const int *mesh)
{
  for (int i = 0; i < 3; ++i)
  {
    // If the address is greater than half the mesh size, 
    // wrap it around by subtracting the mesh size.
    if (address[i] > mesh[i] / 2)
    {
      address[i] -= mesh[i];
    }
  }
}