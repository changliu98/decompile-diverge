int transF(int xr, int xc, float* xp, int tr, int tc, float* tp) {
    if ((xr != tc) || (xc != tr)) {
        return 2000;
    }
    int i, j;
    for (i = 0; i < tr; i++) {
        for (j = 0; j < tc; j++) {
            tp[i * tc + j] = xp[j * xc + i];
        }
    }
    return 0;
}