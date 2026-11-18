void xformSetTranslation(Matrix *mat, float x, float y) {
    // Row 0: [1.0, 0.0, 0.0]
    mat->m[0][0] = 1.0f;
    mat->m[0][1] = 0.0f;
    mat->m[0][2] = 0.0f;
    
    // Row 1: [0.0, 1.0, y]
    mat->m[1][0] = 0.0f;
    mat->m[1][1] = 1.0f;
    mat->m[1][2] = y;
    
    // Row 2: [x, 0.0, 0.0] 
    // Note: The assembly maps `x` to offset 0x10 (m[2][0]) and `y` to 0x14 (m[1][2]).
    // Depending on whether this is row-major or column-major, it sets up the translation vector.
    mat->m[2][0] = x;
    mat->m[2][1] = 0.0f;
    mat->m[2][2] = 0.0f;
}