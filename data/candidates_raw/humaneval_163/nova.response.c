void func0(int a, int b, int *p, int *q) {
    int t;
    *q = 0;
    if (b < a) {
        t = a;
        a = b;
        b = t;
    }
    for (t = a; t <= b; t++) {
        if (t >= 10 && t % 2 == 0) {
            *(p + (*q)++) = t;
        }
    }
}