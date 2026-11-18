void func0(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1],
            double hi[], double e, double o, double t) {
    int i, j; 

    
    hi[0] = e;
    for (i = 1; i < HIDDENNO; ++i)
        hi[i] = wh[i][0] * e;

    
    for (i = 0; i < HIDDENNO; ++i)
        hi[i] *= wo[i] * o;

    
    for (i = 0; i < HIDDENNO; ++i)
        wh[i][INPUTNO] += ALPHA * hi[i] * t;
}