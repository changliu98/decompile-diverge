void reduce_grid_address(long *grid_coords, long *grid_dims)
{
    // Iterate over each dimension of the 3D grid
    for (long dim_idx = 0; dim_idx < 3; dim_idx++) {
        // If the address exceeds half the mesh size, subtract the mesh size to wrap around
        // This effectively maps the address into the range [-mesh[i]/2, mesh[i]/2)
        grid_coords[dim_idx] -= grid_dims[dim_idx] * (long)(int)(uint)(grid_dims[dim_idx] / 2 < grid_coords[dim_idx]);
    }
}