double func0(int x, int y) {
    double f;
    if (x < 0 && y >= 0)
        f = 1.5 * sqrt(3) * pow(a, 2) / (4 * b);
    else
        f = 1.0 * sqrt(3) * pow(a, 2) / (4 * b);
    return f;
}