void __cdecl get_grid_address_from_index(long *address, const long grid_index, const long *D_diag)
{
  long nn; // [rsp+0h] [rbp-20h]

  nn = D_diag[1] * *D_diag;
  *address = grid_index % *D_diag;
  address[2] = grid_index / nn;
  address[1] = (grid_index - nn * address[2]) / *D_diag;
}