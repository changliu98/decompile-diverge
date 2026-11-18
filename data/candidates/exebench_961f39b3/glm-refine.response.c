void __cdecl Mat4_vec3_mul_T(float *v, float *mat, float *src)
{
    float x = src[0];
    float y = src[1];
    float z = src[2];

    // The matrix is treated as a 4x3 matrix (4 columns, 3 rows) 
    // or the transpose of a standard 3x4 matrix, hence the "_T" suffix.
    // Each row computes the dot product of the source vector with a 
    // 3-element column of the matrix, plus an affine translation offset.
    
    float res0 = mat[0] * x + mat[1] * y + mat[2]  * z + mat[3];
    float res1 = mat[4] * x + mat[5] * y + mat[6]  * z + mat[7];
    float res2 = mat[8] * x + mat[9] * y + mat[10] * z + mat[11];

    v[0] = res0;
    v[1] = res1;
    v[2] = res2;
}