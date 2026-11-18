void func0(double *a, double b, double c) {
    if (*a < b)
        *a = b;
    else if (*a > c)
        *a = c;
}