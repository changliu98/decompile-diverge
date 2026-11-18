void matrixApply(const Matrix4x4 *mat, float x, float y, float z, 
                 Vector4 *out1, Vector4 *out2, Vector4 *out3) {
    // Row 1
    out1->x = mat->m[0] * x + mat->m[1] * y + mat->m[2] * z + mat->m[3];
    
    // Row 2
    out2->x = mat->m[4] * x + mat->m[5] * y + mat->m[6] * z + mat->m[7];
    
    // Row 3
    out3->x = mat->m[8] * x + mat->m[9] * y + mat->m[10] * z + mat->m[11];
}