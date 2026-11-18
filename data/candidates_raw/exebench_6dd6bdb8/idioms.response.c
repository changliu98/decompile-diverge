void get_ijl(struct _grid_index *ijl, long grid_index, long *D_diag)
{
  long D_diag_1 = D_diag[1]*D_diag[0];
  ijl->i = grid_index % D_diag[0];
  ijl->l = grid_index / D_diag_1;
  ijl->j = (grid_index - ijl->l*D_diag_1)/D_diag[0];
  return;
}