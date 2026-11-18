A * B
void __cdecl geom_matmat2f(const float *a, const float *b, float *c)
{
    // Cast the flat 1D arrays into 2x2 array pointers for better readability
    const float (*A)[2] = (const float (*)[2])a;
    const float (*B)[2] = (const float (*)[2])b;
    float (*C)[2] = (float (*)[2])c;

    // Row 0 of A multiplied by columns of B
    C[0][0] = (A[0][0] * B[0][0]) + (A[0][1] * B[1][0]);
    C[0][1] = (A[0][0] * B[0][1]) + (A[0][1] * B[1][1]);

    // Row 1 of A multiplied by columns of B
    C[1][0] = (A[1][0] * B[0][0]) + (A[1][1] * B[1][0]);
    C[1][1] = (A[1][0] * B[0][1]) + (A[1][1] * B[1][1]);
}