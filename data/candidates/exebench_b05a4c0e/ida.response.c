void __cdecl grid_point_to_grid_double(int *grid_double, const int grid_point, const int *mesh, const int *is_shift)
{
  int grid[3]; // [rsp+0h] [rbp-30h]
  int i; // [rsp+Ch] [rbp-24h]
  const int *is_shifta; // [rsp+10h] [rbp-20h]
  const int *mesha; // [rsp+18h] [rbp-18h]
  int grid_pointa; // [rsp+24h] [rbp-Ch]
  int *grid_doublea; // [rsp+28h] [rbp-8h]

  grid_doublea = grid_double;
  grid_pointa = grid_point;
  mesha = mesh;
  is_shifta = is_shift;
  grid[2] = grid_point / (mesh[1] * *mesh);
  grid[1] = (grid_point - mesh[1] * *mesh * grid[2]) / *mesh;
  grid[0] = grid_point % *mesh;
  for ( i = 0; i < 3; ++i )
    grid_doublea[i] = is_shifta[i] + 2 * grid[i];
}