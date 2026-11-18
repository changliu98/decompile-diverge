void get_grid_address_from_index(long address[3], long grid_index, long D_diag[3])
{

  address[0] = grid_index % D_diag[0];

  address[2] = grid_index / (D_diag[0]*D_diag[1]);

  address[1] = (grid_index - D_diag[0]*D_diag[1]*address[2]) / D_diag[0];
}