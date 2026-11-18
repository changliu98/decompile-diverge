void __cdecl matmat4(double *A, double *B, double *C, double alpha, double beta)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            double dot = 0.0;
            for (int k = 0; k < 4; ++k)
            {
                dot += A[i * 4 + k] * B[k * 4 + j];
            }
            C[i * 4 + j] = beta * C[i * 4 + j] + alpha * dot;
        }
    }
}