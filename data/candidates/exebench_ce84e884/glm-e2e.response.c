void get_grid_address(long *out, long *a, long *b) {
    for (int i = 0; i < 3; i++) {
        out[i] = (a[i] - b[i]) / 2;
    }
}