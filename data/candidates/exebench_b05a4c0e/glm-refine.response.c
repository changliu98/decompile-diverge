void __cdecl grid_point_to_grid_double(int *grid_double, const int grid_point, const int *mesh, const int *is_shift)
{
    int grid[3];

    // Unroll the 3D grid index (grid_point) into its respective x, y, z components.
    // mesh[0] corresponds to the x-dimension, mesh[1] to y, and mesh[2] to z.
    grid[2] = grid_point / (mesh[1] * mesh[0]);
    grid[1] = (grid_point - mesh[1] * mesh[0] * grid[2]) / mesh[0];
    grid[0] = grid_point % mesh[0];

    // Map the integer grid coordinates to a doubled grid, applying the shift offset.
    // The shift determines if the point is centered (0) or shifted to the boundary (1).
    for (int i = 0; i < 3; ++i)
        grid_double[i] = is_shift[i] + 2 * grid[i];
}