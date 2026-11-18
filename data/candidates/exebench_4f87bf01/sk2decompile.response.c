void reduce_grid_address(long *grid_address, long *grid_size) {
  long i;
  for (i = 0; i < 3; i++) {
    if (grid_address[i] > grid_size[i] / 2) {
      grid_address[i] -= grid_size[i];
    }
  }
}