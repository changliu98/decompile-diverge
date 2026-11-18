void reduce_grid_address_double(int *grid_address, int *grid_size) {
  int i;
  for (i = 0; i < 3; i++) {
    if (grid_address[i] > grid_size[i]) {
      grid_address[i] -= 2 * grid_size[i];
    }
  }
}