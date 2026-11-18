void __cdecl get_grid_address_from_index(long *address, const long grid_index, const long *D_diag)
{
  // Cast pointers to arrays of 3 elements to enable cleaner array indexing
  long (*out)[3] = (long (*)[3])address;
  const long (*dims)[3] = (const long (*)[3])D_diag;

  // Extract grid dimensions for readability
  const long dim_x = (*dims)[0];
  const long dim_y = (*dims)[1];
  
  // Calculate the size of a single 2D slice (x * y)
  const long slice_size = dim_x * dim_y;

  // Unravel the 1D grid_index into 3D coordinates (assuming row-major order)
  (*out)[0] = grid_index % dim_x;                 // X coordinate
  (*out)[2] = grid_index / slice_size;            // Z coordinate
  (*out)[1] = (grid_index % slice_size) / dim_x;  // Y coordinate
}