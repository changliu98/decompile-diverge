int* func0(int **matrix, int n, int size, int *outSize) {
    int start_row = 0, start_col = 0;
    
    // Find the starting position (first occurrence of 1)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                start_row = i;
                start_col = j;
            }
        }
    }
    
    int min_val = n * n;
    
    // Check top neighbor
    if (start_row > 0 && matrix[start_row - 1][start_col] < min_val) {
        min_val = matrix[start_row - 1][start_col];
    }
    
    // Check bottom neighbor
    if (start_row < n - 1 && matrix[start_row + 1][start_col] < min_val) {
        min_val = matrix[start_row + 1][start_col];
    }
    
    // Check left neighbor
    if (start_col > 0 && matrix[start_row][start_col - 1] < min_val) {
        min_val = matrix[start_row][start_col - 1];
    }
    
    // Check right neighbor
    if (start_col < n - 1 && matrix[start_row][start_col + 1] < min_val) {
        min_val = matrix[start_row][start_col + 1];
    }
    
    *outSize = size;
    int *res = (int *)malloc(size * sizeof(int));
    
    // Populate the result array
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            res[i] = 1;
        } else {
            res[i] = min_val;
        }
    }
    
    return res;
}