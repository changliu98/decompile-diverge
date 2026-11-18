void get_grid_double(int *grid_double, int grid_point, int *mesh, int *is_shift)
{
  int i; int j;
  int grid_double_i;
  int grid_point_i;
  int *grid_double_p = grid_double;
  int *mesh_p = mesh;
  int *is_shift_p = is_shift;
  grid_double_i = grid_point / (mesh_p[1]*mesh_p[0]);
  grid_point_i = grid_point - grid_double_i * (mesh_p[1]*mesh_p[0]);
  grid_double_i = grid_point_i / mesh_p[0];
  grid_point_i = grid_point_i - grid_double_i * mesh_p[0];
  i = grid_point_i;
  for (j = 0; j < 3; j++)
  {
    grid_double_p[j] = (is_shift_p[j]) + 2*grid_double_i;
  }
}