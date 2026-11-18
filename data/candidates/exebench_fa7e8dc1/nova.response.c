void fancySwap(int *x, int *y) {
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
}