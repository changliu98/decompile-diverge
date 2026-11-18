void convolve_4(double Q[HIDDENNO][INPUTNO + 1], double X[INPUTNO],
                 double W[HIDDENNO][INPUTNO + 1]) {
    int i, j; 

    
    for (i = 0; i < HIDDENNO; ++i) {
        Q[i][0] = 1.0; 
        for (j = 0; j < INPUTNO; ++j)
            Q[i][j + 1] = X[j] * W[i][j + 1];
    }
}