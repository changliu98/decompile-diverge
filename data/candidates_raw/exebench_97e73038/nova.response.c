int func0(double *p, double *p1, double *p2, double *p3, double *p4,
              double *p5) {
    double x, y, z, a, b, c, d, e, f;
    int i = 0;
    do {
        x = p1[0] - p2[0];
        y = p1[1] - p2[1];
        z = p1[2] - p2[2];
        a = p3[0] - p2[0];
        b = p3[1] - p2[1];
        c = p3[2] - p2[2];
        d = p4[0] - p2[0];
        e = p4[1] - p2[1];
        f = p4[2] - p2[2];
        *p5 = (x * (b * c - e * d) + y * (e * c - a * d) + z * (a * e - b * d));
        if (*p5!= -0.0)
            i = 0;
        else
            i = 1;
    } while (i == 1);
    *p5 = (1.0 / *p5) * (*p);
    *(p + 1) = *p5 * *(p1 + 1);
    *(p + 2) = *p5 * *(p1 + 2);
    *(p + 3) = *p5 * *(p1 + 3);
    return 1;
}