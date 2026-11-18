double KernelBessel_Q1(double x) {
    double p = Pone[4];
    double q = Qone[4];
    long long i = 4;

    while (i >= 0) {
        p = p * (1.0 / x) * (1.0 / x) + Pone[i];
        q = q * (1.0 / x) * (1.0 / x) + Qone[i];
        i--;
    }

    return p / q;
}