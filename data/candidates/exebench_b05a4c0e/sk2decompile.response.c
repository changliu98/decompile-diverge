void grid_point_to_grid_double(int *grid_double, int grid_point, int *grid_size,
                               int *grid_offset) {
  int grid_single[3];
  int i;
  grid_single[2] = grid_point / (grid_size[0] * grid_size[1]);
  grid_single[1] =
      (grid_point - grid_single[2] * grid_size[0] * grid_size[1]) / grid_size[0];
  grid_single[0] = grid_point % grid_size[0];
  for (i = 0; i < 3; i++) {
    grid_double[i] = 2 * grid_single[i] + grid_offset[i];
  }
}