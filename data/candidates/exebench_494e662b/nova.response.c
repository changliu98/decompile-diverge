static void denormF(double x[3], double y[3], double z[3]) {
    double t;
    t = z[0];
    x[0] += y[0] * t;
    x[1] += y[1] * t;
    x[2] += y[2] * t;
    t = z[1];
    y[1] += y[0] * t;
    y[2] += y[1] * t;
    t = z[2];
    z[2] += y[0] * t;
    x[0] *= t;
    y[0] *= t;
    z[0] *= t;
    t = z[0];
    y[1] += y[1] * t;
    y[2] += y[2] * t;
    z[1] += y[1] * t;
    z[2] += y[2] * t;
    t = z[1];
    y[1] *= t;
    y[2] *= t;
    z[1] *= t;
    z[2] *= t;
}