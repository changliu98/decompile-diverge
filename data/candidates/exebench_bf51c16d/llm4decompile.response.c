int condF(int xn, float *xp, int yn, float *yp, int ltn, float *ltp, int eqn, float *eqp, int gtn, float *gtp, int rn, float *rp) {
    int i,j,k;
    float r;

    if (xn != yn || xn != ltn || xn != eqn || xn != gtn || xn != rn) return 2000;

    for (k = 0; k < xn; k++) {
        if (yp[k] > xp[k]) r = ltp[k];
        else if (yp[k] < xp[k]) r = gtp[k];
        else r = eqp[k];
        rp[k] = r;
    }

    return 0;
}