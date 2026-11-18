int* func0(int** grid, int N, int k, int* returnSize)
{
    int x, y;
    int i, j;
    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
            if (grid[i][j] == 1) {
                x = i;
                y = j;
            }
    int min = N * N;
    if (x > 0 && grid[x - 1][y] < min)
        min = grid[x - 1][y];
    if (x < N - 1 && grid[x + 1][y] < min)
        min = grid[x + 1][y];
    if (y > 0 && grid[x][y - 1] < min)
        min = grid[x][y - 1];
    if (y < N - 1 && grid[x][y + 1] < min)
        min = grid[x][y + 1];
    *returnSize = k;
    int* result = (int*)malloc((size_t)k * sizeof(int));
    for (i = 0; i < k; ++i)
        result[i] = i % 2 ? min : 1;
    return result;
}