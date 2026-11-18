void func0(int *x, int *y, int a, int b) {
    if (*x == *y) {
        *x = a;
        *y = b;
    } else if (a < *x) {
        *x = a;
        if (b > *y)
            *y = b;
    }
}