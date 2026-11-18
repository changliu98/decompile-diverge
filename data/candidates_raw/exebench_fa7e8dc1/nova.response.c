void func0(int *x, int *y) {
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
}