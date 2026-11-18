void get_grid_address_from_index(long *address,long grid_index,long *D_diag)

{
  long lVar1;
  long lVar2;
  long nn;
  long *D_diag_local;
  long grid_index_local;
  long *address_local;
  
  lVar1 = *D_diag;
  lVar2 = D_diag[1];
  *address = grid_index % *D_diag;
  address[2] = grid_index / (lVar1 * lVar2);
  address[1] = (grid_index - address[2] * lVar1 * lVar2) / *D_diag;
  return;
}