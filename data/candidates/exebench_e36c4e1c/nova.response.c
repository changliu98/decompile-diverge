void matmat4(double a[3], double b[3], double c[3], double t) {
    c[0] = (1 - t) * a[0] + t * b[0];
    c[1] = (1 - t) * a[1] + t * b[1];
    c[2] = (1 - t) * a[2] + t * b[2];
}