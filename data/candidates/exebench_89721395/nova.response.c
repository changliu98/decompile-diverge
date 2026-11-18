int matM4toM3(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1]) {
    int i, j;
    for (i = 0; i < HIDDENNO; ++i)
        for (j = 0; j < INPUTNO + 1; ++j)
            wo[i] = wh[i][j];
    return 0;
}