void func0(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1]) {
    int i, j; 

    
    for (i = 0; i < HIDDENNO; ++i)
        for (j = 0; j < INPUTNO + 1; ++j)
            wh[i][j] = drand();

    
    for (i = 0; i < HIDDENNO + 1; ++i)
        wo[i] = drand();
}