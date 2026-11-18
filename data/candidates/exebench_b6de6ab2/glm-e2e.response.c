void reduce_grid_address(int *grid_address, int *grid_mapping_table) {
    for (int i = 0; i < 3; i++) {
        int is_bigger = grid_address[i] > (grid_mapping_table[i] / 2);
        grid_address[i] -= is_bigger * grid_mapping_table[i];
    }
}