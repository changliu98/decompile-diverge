long sort_omegas(double *d) {
    long i, j;
    double t;
    long k = 0;

    if (d[1] > d[2]) {
        t = d[2];
        d[2] = d[1];
        d[1] = t;
        k = 1;
    }
    if (d[0] > d[2]) {
        t = d[2];
        d[2] = d[0];
        d[0] = t;
        if (k == 0)
            k = 4;
        else if (k == 1)
            k = 3;
    }
    if (d[1] > d[2]) {
        t = d[2];
        d[2] = d[1];
        d[1] = t;
        if (k == 1)
            k = 5;
        else if (k == 4)
            k = 2;
    }
    if (d[1] > d[2]) {
        t = d[2];
        d[2] = d[1];
        d[1] = t;
        if (k == 4)
            k = 1;
        else if (k == 5)
            k = 2;
    }
    return k;
}