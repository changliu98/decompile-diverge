double func0(double x, double y) {
    double t = sqrt(x * x + y * y);
    double a = (x + t) * (x + t) * M_PI * x;
    return a;
}