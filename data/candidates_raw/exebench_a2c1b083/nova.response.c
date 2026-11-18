void func0(double A[3][3], double B[3][3], double C[3][3], double a, double b) {
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            C[i][j] = a * A[i][j] + b * B[i][j];
}