void reduce_grid_address(int *grid_coords, int *grid_dims)
{
  // Iterate over each dimension (x, y, z)
  for (int i = 0; i < 3; i++) {
    // If the current address component is greater than half the mesh size,
    // subtract the mesh size to wrap the address into the range [-mesh/2, mesh/2).
    // The expression (mesh[i] / 2 < address[i]) evaluates to 1 if true, 0 otherwise.
    grid_coords[i] -= grid_dims[i] * (uint)(grid_dims[i] / 2 < grid_coords[i]);
  }
}