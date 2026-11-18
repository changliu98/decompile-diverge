void __cdecl matmult(float A[4][4], float B[4][4], float C[4][4])
{
    int i, j, k;

    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            C[i][j] = 0.0f;
            for (k = 0; k < 4; ++k)
            {
                // Equivalent to: C[i][j] += A[i][k] * B[k][j];
                C[i][j] = (A[i][k] * B[k][j]) + C[i][j];
            }
        }
    }
}