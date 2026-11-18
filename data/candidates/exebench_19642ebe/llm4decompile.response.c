void multiply_naive(float A[4][4], float B[4][4], float result[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result[i][j] = B[i][0] * A[0][j] + B[i][1] * A[1][j] + B[i][2] * A[2][j] + B[i][3] * A[3][j];
        }
    }
}