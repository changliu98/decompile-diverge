double blue_filter(double t, double y[NEQ]) {
    double dydt[NEQ];
    dydt[0] = -0.04 * y[0] + 1.0e4 * y[1] * y[2];
    dydt[1] = 0.04 * y[0] - 1.0e4 * y[1] * y[2] - 3.0e7 * y[1] * y[1];
    dydt[2] = 3.0e7 * y[1] * y[1];
    dydt[3] = -1.01 * y[3] + 1.0e4 * y[1] * y[2];
    dydt[4] = 1.01 * y[3] - 1.0e4 * y[1] * y[2] - 3.0e7 * y[3] * y[3];
    dydt[5] = 3.0e7 * y[3] * y[3];
    return 1.0e-4 * (dydt[0] + dydt[1] + dydt[2] + dydt[3] + dydt[4] + dydt[5]);
}