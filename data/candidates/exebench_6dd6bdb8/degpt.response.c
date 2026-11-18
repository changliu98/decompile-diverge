void get_grid_address_from_index(long *grid_coords, long linear_index, long *diag_dims)
{
    // Extract the first two dimensions from the diagonal matrix D_diag
    long dim_x = *diag_dims;
    long dim_y = diag_dims[1];
    
    // Calculate the first coordinate (x) using modulo operation
    *grid_coords = linear_index % dim_x;
    
    // Calculate the third coordinate (z) by integer division
    grid_coords[2] = linear_index / (dim_x * dim_y);
    
    // Calculate the second coordinate (y) by subtracting the contribution of z and then dividing by lVar1
    grid_coords[1] = (linear_index - grid_coords[2] * dim_x * dim_y) / dim_x;
}