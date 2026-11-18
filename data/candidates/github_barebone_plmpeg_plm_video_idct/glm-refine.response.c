void __cdecl plm_video_idct(int *block) {
    // Treat the 1D array as an 8x8 matrix for readability
    int (*mat)[8] = (int (*)[8])block;
    int temp[8];
    
    // 1st pass: Apply IDCT vertically on columns (no down-shift)
    for (int col = 0; col < 8; ++col) {
        int in_col[8] = { 
            mat[0][col], mat[1][col], mat[2][col], mat[3][col],
            mat[4][col], mat[5][col], mat[6][col], mat[7][col] 
        };
        
        idct_1d(in_col, temp, 0);
        
        // Store intermediate results back to the column
        for (int row = 0; row < 8; ++row) {
            mat[row][col] = temp[row];
        }
    }
    
    // 2nd pass: Apply IDCT horizontally on rows (with 8-bit down-shift)
    for (int row = 0; row < 8; ++row) {
        idct_1d(mat[row], mat[row], 8);
    }
}