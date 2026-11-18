void __cdecl reduce_grid_address_double(int *address, const int *mesh)
{
  for (int i = 0; i < 3; ++i)
  {
    // If the address is strictly greater than the mesh boundary,
    // shift it back into the periodic cell by subtracting 2 * mesh.
    if (address[i] > mesh[i])
    {
      address[i] -= 2 * mesh[i];
    }
  }
}