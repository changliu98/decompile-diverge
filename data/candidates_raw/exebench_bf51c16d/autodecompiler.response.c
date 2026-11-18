int eppInf(int xn, float* xp, int yn, float* yp, int ltn, float* lp, int gtn, float* gp, int eqn, float* ep, int rn, float* rp) {
    int i, j;
    float min, max;

    if ((xn != yn) || (xn != ltn) || (xn != eqn) || (xn != gtn) || (xn != rn)) {
        printf__bench("Error: Array lengths are not equal.\n");
        return(2000);
    }

    for (i = 0; i < xn; i++) {
        if (xp[i] < yp[i]) {
            min = lp[i];
        } else if (xp[i] > yp[i]) {
            min = gp[i];
        } else {
            min = ep[i];
        }
        if (xp[i] < yp[i]) {
            max = gp[i];
        } else if (xp[i] > yp[i]) {
            max = lp[i];
        } else {
            max = ep[i];
        }
        rp[i] = min;
        rp[i] = max;
    }

    return(0);
}