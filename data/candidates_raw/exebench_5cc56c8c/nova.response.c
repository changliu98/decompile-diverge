void func0(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1],
            double hi[], double e[INPUTNO + 1]) {
    int i, j; 

    
    for (i = 0; i < HIDDENNO; ++i) {
        hi[i] = wo[i];
        for (j = 0; j < INPUTNO; ++j)
            hi[i] += e[j] * wh[i][j];
        hi[i] = sigmoid(hi[i]);
    }
}