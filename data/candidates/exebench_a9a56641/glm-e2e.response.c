void Mat4_inv_Mat4_affine_mul(Mat4 *A, const Mat4 *B, const Mat4 *C) {
    Mat4 res;
    
    // Compute the inverse of the 3x3 rotation/scale part of B
    // and multiply it by the 3x3 rotation/scale part of C.
    // The inverse of a 3x3 matrix is its transpose if it's orthogonal,
    // which matches the pattern of accessing B's elements column-major.
    res.m[0][0] = -(B->m[0][0] * B->m[3][0] + B->m[0][1] * B->m[3][1] + B->m[0][2] * B->m[3][2]);
    res.m[0][1] = -(B->m[1][0] * B->m[3][0] + B->m[1][1] * B->m[3][1] + B->m[1][2] * B->m[3][2]);
    res.m[0][2] = -(B->m[2][0] * B->m[3][0] + B->m[2][1] * B->m[3][1] + B->m[2][2] * B->m[3][2]);
    
    res.m[1][0] = B->m[0][0] * C->m[0][0] + B->m[0][1] * C->m[1][0] + B->m[0][2] * C->m[2][0];
    res.m[1][1] = B->m[1][0] * C->m[0][0] + B->m[1][1] * C->m[1][0] + B->m[1][2] * C->m[2][0];
    res.m[1][2] = B->m[2][0] * C->m[0][0] + B->m[2][1] * C->m[1][0] + B->m[2][2] * C->m[2][0];
    res.m[1][3] = 0.0f;
    
    res.m[2][0] = B->m[0][0] * C->m[0][1] + B->m[0][1] * C->m[1][1] + B->m[0][2] * C->m[2][1];
    res.m[2][1] = B->m[1][0] * C->m[0][1] + B->m[1][1] * C->m[1][1] + B->m[1][2] * C->m[2][1];
    res.m[2][2] = B->m[2][0] * C->m[0][1] + B->m[2][1] * C->m[1][1] + B->m[2][2] * C->m[2][1];
    res.m[2][3] = 0.0f;
    
    res.m[3][0] = B->m[0][0] * C->m[0][2] + B->m[0][1] * C->m[1][2] + B->m[0][2] * C->m[2][2];
    res.m[3][1] = B->m[1][0] * C->m[0][2] + B->m[1][1] * C->m[1][2] + B->m[1][2] * C->m[2][2];
    res.m[3][2] = B->m[2][0] * C->m[0][2] + B->m[2][1] * C->m[1][2] + B->m[2][2] * C->m[2][2];
    res.m[3][3] = 0.0f;
    
    // Compute the translation part: -inv(B.rotation) * B.translation + inv(B.rotation) * C.translation
    res.m[0][3] = res.m[0][0] + B->m[0][0] * C->m[3][0] + B->m[0][1] * C->m[3][1] + B->m[0][2] * C->m[3][2];
    res.m[1][3] = res.m[0][1] + B->m[1][0] * C->m[3][0] + B->m[1][1] * C->m[3][1] + B->m[1][2] * C->m[3][2];
    res.m[2][3] = res.m[0][2] + B->m[2][0] * C->m[3][0] + B->m[2][1] * C->m[3][1] + B->m[2][2] * C->m[3][2];
    res.m[3][3] = 1.0f; // Loaded from memory constant at 0x2004
    
    *A = res;
}