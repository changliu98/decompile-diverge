void getTransf(const double wh[HIDDENNO][INPUTNO + 1],
                 const double wo[HIDDENNO + 1], double h[HIDDENNO]) {
    int i, j; 

    for (i = 0; i < HIDDENNO; ++i) {
        h[i] = wh[i][INPUTNO];
        for (j = 0; j < INPUTNO; ++j)
            h[i] += wh[i][j] * x[j];
        h[i] = sigmoid(h[i]);
    }
}