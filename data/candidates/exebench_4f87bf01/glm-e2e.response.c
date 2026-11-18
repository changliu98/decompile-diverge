void reduce_grid_address(long *grid_address, long *grid_size) {
    for (long i = 0; i < 3; i++) {
        long q = grid_size[i] / 2;
        long val = grid_address[i];
        long sub = (val > q) ? grid_size[i] : 0;
        grid_address[i] -= sub;
    }
}