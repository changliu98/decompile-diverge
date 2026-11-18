int pos2ddd(long int x, long int y, double *a, double *b) {
    *a = (double)(x) / 100000.0 + (double)(x % 100000) / 100000000.0;
    *b = (double)(y) / 100000.0 + (double)(y % 100000) / 100000000.0;
    return 0;
}