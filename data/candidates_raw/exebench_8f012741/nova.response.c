void func0(double wh[2], double r[2], double u[2]) {
    double d = (r[1] * u[0] + r[0] * u[1]) / (u[1] * r[1] + u[0] * r[0]);
    wh[0] = d * u[0] * r[0];
    wh[1] = d * u[1] * r[1];
}