void ifft8pt(float *a, float b) {
    float c[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            c[i][j] = a[i * 4 + j];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            a[i * 4 + j] = c[i][j] + b * c[j][i];
}