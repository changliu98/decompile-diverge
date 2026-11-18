float Intersect(float *matrix, int row1, int row2, int cols) {
    float intersect_count = 0.0f;
    float count_row1 = 0.0f;
    float count_row2 = 0.0f;
    
    for (int i = 0; i < cols; i++) {
        // Check if both elements are 0.0f (intersection of zeros)
        if (matrix[row1 * cols + i] == 0.0f && matrix[row2 * cols + i] == 0.0f) {
            intersect_count += 1.0f;
        }
        
        // Count zeros in row1
        if (matrix[row1 * cols + i] == 0.0f) {
            count_row1 += 1.0f;
        }
        
        // Count zeros in row2
        if (matrix[row2 * cols + i] == 0.0f) {
            count_row2 += 1.0f;
        }
    }
    
    // Compute the ratio based on the maximum of the two counts
    if (count_row2 > count_row1) {
        return intersect_count / count_row1;
    } else {
        return intersect_count / count_row2;
    }
}