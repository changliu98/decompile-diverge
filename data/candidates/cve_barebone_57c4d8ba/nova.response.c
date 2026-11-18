int compile_get_env(long *p, long *q) {
    int i, j, k;
    long x, y, z;
    long a, b, c, d;
    int res;

    a = *p;
    b = *p;
    *p = *p + 1;
    c = f(a);
    if (c == 0) {
        printf("Error %ld\n", a - 1);
        res = 0;
    } else {
        x = malloc(c + 1);
        res = func01(x, 0, 0, q);
        free(x);
    }
    return res;
}