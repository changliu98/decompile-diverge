int func0(int **matrix, int rows, int cols, int divisor) {
    int total = 0;
    
    for (int i = 0; i < rows; i++) {
        int row_sum = 0;
        
        for (int j = 0; j < cols; j++) {
            row_sum += matrix[i][j];
        }
        
        if (row_sum > 0) {
            total += (row_sum + divisor - 1) / divisor;
        }
    }
    
    return total;
}