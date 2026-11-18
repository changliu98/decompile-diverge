void grid_point_to_grid_double(double grid[3], int grid_point, int mesh[3], int is_shift[3])
{
  int i;
  int grid_int[3];

  grid_int[2] = grid_point / (mesh[0] * mesh[1]);
  grid_int[1] = (grid_point - grid_int[2] * mesh[0] * mesh[1]) / mesh[0];
  grid_int[0] = grid_point % mesh[0];

  for(i = 0; i < 3; i++)
    grid[i] = 2 * grid_int[i] + is_shift[i];
}