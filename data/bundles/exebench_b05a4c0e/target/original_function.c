static void grid_point_to_grid_double(int grid_double[3],
          const int grid_point,
          const int mesh[3],
          const int is_shift[3])
{
  int i;
  int grid[3];


  grid[2] = grid_point / (mesh[0] * mesh[1]);
  grid[1] = (grid_point - grid[2] * mesh[0] * mesh[1]) / mesh[0];
  grid[0] = grid_point % mesh[0];






  for (i = 0; i < 3; i++) {
    grid_double[i] = grid[i] * 2 + is_shift[i];
  }
}