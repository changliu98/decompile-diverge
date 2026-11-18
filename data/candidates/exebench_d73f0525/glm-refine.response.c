void __cdecl geom_matmat4f(const float *a, const float *b, float *c)
{
    const float (*A)[4] = AS_MAT4(a);
    const float (*B)[4] = AS_MAT4(b);
    float (*C)[4] = AS_MAT4(c);

    for (ptrdiff_t i = 0; i < 4; ++i)
    {
        C[0][i] = A[0][i] * B[i][0] + A[1][i] * B[i][1] + A[2][i] * B[i][2] + A[3][i] * B[i][3];
        C[1][i] = A[0][i] * B[i][4] + A[1][i] * B[i][5] + A[2][i] * B[i][6] + A[3][i] * B[i][7];
        C[2][i] = A[0][i] * B[i][8] + A[1][i] * B[i][9] + A[2][i] * B[i][10] + A[3][i] * B[i][11];
        C[3][i] = A[0][i] * B[i][12] + A[1][i] * B[i][13] + A[2][i] * B[i][14] + A[3][i] * B[i][15];
    }
}