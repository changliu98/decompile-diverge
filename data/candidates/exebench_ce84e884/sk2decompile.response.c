void get_grid_address(long *grid_address, double *position, long *grid_size) {
  int i;
  for (i = 0; i < 3; i++) {
    grid_address[i] = (long)((position[i] - grid_size[i]) / 2);
  }
}