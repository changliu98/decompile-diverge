double func0(double x, double y) {
    double t;
    double func0;
    t = x * 360.0 / 65536.0;
    if (y >= 65536.0 / 2)
        func0 = 360.0;
    else
        func0 = t * y * 360.0 / 65536.0;
    return func0;
}