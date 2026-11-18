int func0(int a, int b, int c, int d, int *x, int *y, int *z) {
    int e, f, g;

    if (a!= c) {
        if (a < c)
            e = a;
        else
            e = c;
    } else
        e = -1;
    *x = e;

    if (b!= d) {
        if (b < d)
            f = b;
        else
            f = d;
    } else
        f = -1;
    *y = f;

    if (e!= -1)
        g = e;
    else
        g = f;
    *z = g;

    return 0;
}