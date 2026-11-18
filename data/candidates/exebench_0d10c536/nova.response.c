void bitrv216(double f[2][2]) {
    double temp[2][2];
    int i, j;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            temp[i][j] = f[i][j];
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            f[i][j] = temp[j][i];
}