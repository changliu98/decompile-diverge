void grid_point_to_grid_double(int *grid_double_out, int grid_point_idx, int *mesh_size, int *shift_values)
{
    int grid_indices[3];
    int idx;

    // Calculate the z-component of the grid point index
    grid_indices[2] = grid_point_idx / (*mesh_size * mesh_size[1]);
    // Calculate the y-component of the grid point index
    grid_indices[1] = (grid_point_idx - grid_indices[2] * *mesh_size * mesh_size[1]) / *mesh_size;
    // Calculate the x-component of the grid point index
    grid_indices[0] = grid_point_idx % *mesh_size;
    // Convert grid indices to double-precision values with shift applied
    for (idx = 0; idx < 3; idx++) {
        grid_double_out[idx] = grid_indices[idx] * 2 + shift_values[idx];
    }
}