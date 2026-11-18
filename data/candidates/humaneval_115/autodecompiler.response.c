int func0(int** grid, int m, int n, int k) {
    int total = 0;
    for (int i = 0; i < m; ++i) {
        int sum = 0;
        for (int j = 0; j < n; ++j) {
            sum += grid[i][j];
        }
        if (sum > 0) {
            total += (sum + k - 1) / k;
        }
    }
    return total;
}