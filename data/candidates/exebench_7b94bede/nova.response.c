void mlMatrixTransposeTo(float *a, float *b) {
    unsigned int i, j;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            b[i * 5 + j] = a[j * 5 + i];
}