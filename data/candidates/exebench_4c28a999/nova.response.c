void fb_hFixCoordsOrder(int *x, int *y, int *z, int *w) {
    if (*z < *x) {
        *x = *x ^ *z;
        *z = *x ^ *z;
        *x = *x ^ *z;
    }
    if (*w < *y) {
        *y = *y ^ *w;
        *w = *y ^ *w;
        *y = *y ^ *w;
    }
}