void upzero(int d, int *dq, int *dlt) {
    int i;
    int wkbl;
    int wd;

    if (d == 0) {
        for (i = 0; i < 6; i++) {
            wd = (dlt[i] * 255) >> 8;
            dlt[i] = wd;
        }
    } else {
        for (i = 0; i < 6; i++) {
            wkbl = (d * dq[i]) < 0 ? -128 : 128;
            wd = (dlt[i] * 255) >> 8;
            dlt[i] = wd + wkbl;
        }
    }

    dq[5] = dq[4];
    dq[4] = dq[3];
    dq[3] = dq[2];
    dq[2] = dq[1];
    dq[1] = dq[0];
    dq[0] = d;
}