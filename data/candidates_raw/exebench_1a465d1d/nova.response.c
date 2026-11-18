void func0(double x, double y, double z, double t, double *out) {
    double a, b, c, d, e, f, g;

    a = 1.0 / (z - x);
    b = 1.0 / (y - x);
    c = 1.0 / (t - x);
    d = 1.0 / (t - y);
    e = 1.0 / (t - z);

    f = a + b + c;
    g = a * b + b * c + c * a;

    out[0] = f * a;
    out[1] = f * b;
    out[2] = f * c;
    out[3] = -g * a * b;
    out[4] = -g * b * c;
    out[5] = -g * c * a;
    out[6] = g * a * c;
    out[7] = g * b * a;
    out[8] = g * c * b;
}