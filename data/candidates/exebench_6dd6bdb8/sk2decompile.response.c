void get_grid_address_from_index(long *grid_address, long index, long *dims) {
  long nxny;
  nxny = dims[0] * dims[1];
  grid_address[0] = index % dims[0];
  grid_address[2] = index / nxny;
  grid_address[1] = (index - grid_address[2] * nxny) / dims[0];
}