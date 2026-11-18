double func0(int n) {
    double t, s;
    t = pow(2, n);
    s = pow(3, 0.5);
    return round(t / (s * pow(2, n)));
}