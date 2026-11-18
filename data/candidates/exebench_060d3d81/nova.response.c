void quatmul(double Q[HIDDENNO][INPUTNO + 1], double X[INPUTNO],
                double W[HIDDENNO][INPUTNO + 1]) {
    int i, j; 

    
    for (i = 0; i < HIDDENNO; ++i)
        for (j = 0; j < INPUTNO + 1; ++j)
            Q[i][j] = X[j] * W[i][j];
}