void func0(double x[2], double u[2], double v[2], double w[2]) {
    x[0] = u[0] + v[0] * w[1] + w[0] * v[1];
    x[1] = u[1] + v[0] * w[1] + w[0] * v[1];
}