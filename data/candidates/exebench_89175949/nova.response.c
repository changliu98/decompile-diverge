int foo(int *x, int *y, int z) {
    *x = *x << 1;
    *y = *y / 2;
    z = *x + *y;
    return z;
}