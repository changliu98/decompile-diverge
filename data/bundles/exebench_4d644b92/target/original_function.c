int twiddle1(int *xp, int *yp) {
    *xp += *yp;
    *xp += *yp;
    return *xp;
}