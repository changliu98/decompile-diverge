void grid_point_to_grid_double(int *grid_double,int grid_point,int *mesh,int *is_shift)

{
  int grid [3];
  int i;
  int *is_shift_local;
  int *mesh_local;
  int grid_point_local;
  int *grid_double_local;
  
  grid[2] = grid_point / (*mesh * mesh[1]);
  grid[1] = (grid_point - grid[2] * *mesh * mesh[1]) / *mesh;
  grid[0] = grid_point % *mesh;
  for (i = 0; i < 3; i = i + 1) {
    grid_double[i] = grid[i] * 2 + is_shift[i];
  }
  return;
}