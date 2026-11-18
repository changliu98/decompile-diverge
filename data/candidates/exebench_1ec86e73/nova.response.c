double frexp(double x) {
    int sign = 1;
    if (x < 0) {
        sign = -1;
        x = -x;
    }
    if (x == 0) {
        e = 0;
        return 0;
    }
    e = 1;
    double t = 1;
    double y = x;
    while (1) {
        if (y >= 10 || y <= -10) {
            y /= t;
            t *= 2;
            continue;
        }
        e++;
    }
    return y * sign;
}