static void get_grid_address_from_index(long address[3],
                                        const long grid_index,
                                        const long D_diag[3])
{
  long nn;


  nn = D_diag[0] * D_diag[1];
  address[0] = grid_index % D_diag[0];
  address[2] = grid_index / nn;
  address[1] = (grid_index - address[2] * nn) / D_diag[0];






}