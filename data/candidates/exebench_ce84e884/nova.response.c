void get_grid_address(long long *ans, long long *a, long long *b) {
    int i;
    for (i = 0; i < 4; i++) {
        ans[i] = (a[i] - b[i]) / 2;
    }
}