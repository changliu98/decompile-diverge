void bitrv216neg(double m[L][C]) {
    double temp;
    int i, j;
    for (i = 0; i < L; i++)
        for (j = 0; j < C; j++) {
            temp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = temp;
        }
}