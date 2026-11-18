void matvec4(double *mat, double *vec, double *out, double add0, double add1) {
    // The function signature is inferred from the registers:
    // rdi = mat (4x4 matrix, 16 doubles)
    // rsi = vec (4D vector, 4 doubles)
    // rdx = out (4D vector, 4 doubles)
    // xmm0 = add0 (scalar added to out[0])
    // xmm1 = add1 (scalar added to out[1], out[2], and out[3])
    
    out[0] = mat[0] * vec[0] + mat[1] * vec[1] + mat[2] * vec[2] + mat[3] * vec[3] + add0;
    out[1] = mat[4] * vec[0] + mat[5] * vec[1] + mat[6] * vec[2] + mat[7] * vec[3] + add1;
    out[2] = mat[8] * vec[0] + mat[9] * vec[1] + mat[10] * vec[2] + mat[11] * vec[3] + add1;
    out[3] = mat[12] * vec[0] + mat[13] * vec[1] + mat[14] * vec[2] + mat[15] * vec[3] + add1;
}