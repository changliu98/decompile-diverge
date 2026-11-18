int func0(int a, int b, int *x, int *y) {
    int ret;
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    ret = func0(b, a % b, y, x);
    int tmp = *x;
    *x = *y;
    *y = tmp - (a / b) * (*y);
    return ret;
}