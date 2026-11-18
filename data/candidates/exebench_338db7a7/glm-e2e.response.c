void reduce_grid_address_double(int *grid_address, int *dgrid) {
    for (int i = 0; i < 3; i++) {
        int val = dgrid[i] * 2;
        if (grid_address[i] > dgrid[i]) {
            grid_address[i] -= val;
        }
    }
}