int func0(int **grid, int rows, int cols, int capacity)
{
    int i, j, sum, ret = 0;

    for (i = 0; i < rows; i++) {
        sum = 0;
        for (j = 0; j < cols; j++) {
            sum += grid[i][j];
        }
        if (sum > 0) {
            ret += (sum + capacity - 1) / capacity;
        }
    }

    return ret;
}