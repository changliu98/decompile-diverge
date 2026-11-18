int func0(double *p, double *q, double *r, double *s, double *t,
               double *u) {
    double a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p1, q1, r1, s1, t1, u1;
    int flag = 0;
    do {
        a = (s[1] - r[1]) * (t[0] - r[0]);
        b = (s[0] - r[0]) * (t[1] - r[1]);
        c = (s[1] - r[1]) * (t[0] - s[0]);
        d = (s[0] - r[0]) * (t[1] - s[1]);
        e = (t[0] - r[0]) * (u[1] - r[1]);
        f = (t[1] - r[1]) * (u[0] - r[0]);
        g = (t[0] - r[0]) * (u[1] - t[1]);
        h = (t[1] - r[1]) * (u[0] - t[0]);
        i = (u[0] - r[0]) * (u[1] - r[1]);
        j = (u[1] - r[1]) * (u[0] - s[0]);
        k = (u[0] - s[0]) * (u[1] - t[1]);
        l = (u[1] - t[1]) * (u[0] - r[0]);
        m = (u[0] - r[0]) * (u[1] - r[1]);
        n = (u[1] - r[1]) * (u[0] - r[0]);
        o = (u[0] - r[0]) * (u[1] - r[1]);
        p1 = a + b + c + d;
        q1 = e + f + g + h;
        r1 = i + j + k + l;
        s1 =