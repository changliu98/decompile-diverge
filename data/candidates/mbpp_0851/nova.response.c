double func0(int n, int k) {
    double p;
    p = (double)k / n;
    return (double)round(log(1 - p) / log(p));
}