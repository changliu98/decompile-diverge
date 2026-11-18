/**
 * Adjusts grid address to handle periodic boundary conditions.
 *
 * For each dimension, if the address exceeds the mesh size,
 * it subtracts twice the mesh size to wrap the address back
 * into the valid range [0, mesh[i]-1].
 *
 * @param address Pointer to the 3D grid address array.
 * @param mesh    Pointer to the 3D mesh size array.
 */
void reduce_grid_address_double(int *grid_coords, int *domain_size)
{
    // Iterate over each of the 3 spatial dimensions
    for (int dim_idx = 0; dim_idx < 3; dim_idx++) {
        // If address[i] is greater than mesh[i], subtract 2 * mesh[i]
        // to wrap the address around the periodic boundary.
        // The cast to uint ensures the condition evaluates correctly
        // for signed integer comparison.
        grid_coords[dim_idx] -= domain_size[dim_idx] * 2 * (uint)(domain_size[dim_idx] < grid_coords[dim_idx]);
    }
}