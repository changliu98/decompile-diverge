double func0(double x, int k) {
    double p = pow(2, -k);
    double y = ceil(x / p) * p;
    double z = ceil(y / 2) * 2;
    return z / pow(2, k);
}